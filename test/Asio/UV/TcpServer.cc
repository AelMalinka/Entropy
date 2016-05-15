/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Asio/UV/Application.hh"
#include "Asio/UV/Tcp.hh"
#include "Process.hh"
#include <gtest/gtest.h>

using namespace std;
using namespace Entropy;
using namespace testing;

#define TEST_BEGIN try {
#define TEST_END } catch(exception &e) { FAIL() << e << endl; }

namespace {
	class TcpServerTest :
		public Asio::UV::Application,
		public Test
	{
		public:
			TcpServerTest();
			~TcpServerTest();
		protected:
			void onConnect(Asio::UV::Stream &);
			void onDisconnect(Asio::UV::Stream &);
			void onData(Asio::UV::Stream &, const string &);
			void onError(const Exception &);
		protected:
			Asio::UV::Tcp _server;
			function<void(Asio::UV::Stream &)> _on_con;
			function<void(Asio::UV::Stream &)> _on_disco;
			function<void(Asio::UV::Stream &, const string &)> _on_data;
	};

	TcpServerTest::TcpServerTest()
		: Asio::UV::Application(), Test(), _server(Loop(), bind(&TcpServerTest::onConnect, ref(*this), placeholders::_1), bind(&TcpServerTest::onDisconnect, ref(*this), placeholders::_1), bind(&TcpServerTest::onData, ref(*this), placeholders::_1, placeholders::_2), bind(&TcpServerTest::onError, ref(*this), placeholders::_1)), _on_con(), _on_disco(), _on_data()
	{}

	TcpServerTest::~TcpServerTest()
	{}

	void TcpServerTest::onConnect(Asio::UV::Stream &s)
	{
		if(_on_con)
			_on_con(s);
	}

	void TcpServerTest::onDisconnect(Asio::UV::Stream &s)
	{
		if(_on_disco)
			_on_disco(s);
	}

	void TcpServerTest::onData(Asio::UV::Stream &s, const string &d)
	{
		if(_on_data)
			_on_data(s, d);
	}

	void TcpServerTest::onError(const Exception &e)
	{
		throw e;
	}

	TEST_F(TcpServerTest, Initialize) {
	}

	TEST_F(TcpServerTest, Connect) {
		TEST_BEGIN
			_on_disco = [this](auto &) {
				_server.Disconnect();
			};

			_server.Listen("localhost", "9081");
			Process p("echo -e '\n' | socat - tcp:localhost:9081");

			(*this)();

			EXPECT_EQ(p.Return(), 0);
		TEST_END
	}

	TEST_F(TcpServerTest, ReadWrite) {
		TEST_BEGIN
			string send = "And to you too!";
			string data;

			_on_con = [&send](auto &s) {
				s.Write(send + "\n");
			};
			_on_disco = [this](auto &) {
				_server.Disconnect();
			};
			_on_data = [&data](auto &, auto d) {
				data = d;
			};

			_server.Listen("localhost", "9081");
			Process p("echo 'Hello World!' | socat - tcp:localhost:9081");

			(*this)();

			string out;
			getline(p.Out(), out);

			EXPECT_EQ(p.Return(), 0);
			EXPECT_EQ(data, "Hello World!\n"s);
			EXPECT_EQ(out, send);
		TEST_END
	}

	TEST_F(TcpServerTest, MultiRead) {
		TEST_BEGIN
			string send = "Hello World!\n";
			string total_send;
			string data;
			size_t count = 20;
			size_t len = 0;
			size_t clients = 0;
			size_t disco = count;
			vector<shared_ptr<Process>> v;

			for(size_t x = 0; x < count; x++)
				total_send += send;
			size_t total_len = total_send.size();

			_on_con = [&clients](auto &) {
				++clients;
			};
			_on_disco = [&clients, &disco, count, this](auto &) {
				--disco;
				if(disco == 0 && clients == count)
					_server.Disconnect();
			};
			_on_data = [&data, &len](auto &, auto d) {
				data += d;
				len += d.size();
			};

			_server.Listen("localhost", "9081");
			for(size_t x = 0; x < count; x++)
				v.push_back(make_shared<Process>("sleep .1s && echo -n '" + send + "' | socat - tcp:localhost:9081"));

			(*this)();

			EXPECT_EQ(data, total_send);
			EXPECT_EQ(len, total_len);

			for(auto &x : v)
				EXPECT_EQ(x->Return(), 0);
		TEST_END
	}
}
