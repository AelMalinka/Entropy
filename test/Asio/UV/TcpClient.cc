/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Asio/UV/Application.hh"
#include "Asio/UV/Tcp.hh"
#include "Process.hh"
#include <gtest/gtest.h>
#include <unistd.h>

using namespace std;
using namespace Entropy;
using namespace testing;

#define TEST_BEGIN try {
#define TEST_END } catch(exception &e) { FAIL() << e << endl; }

namespace {
	class TcpClientTest :
		public Asio::UV::Application,
		public Test
	{
		public:
			TcpClientTest();
			~TcpClientTest();
		protected:
			void onConnect(Asio::UV::Stream &);
			void onDisconnect(Asio::UV::Stream &);
			void onData(Asio::UV::Stream &, const string &);
			void onError(const Exception &);
		protected:
			Process _server;
			Asio::UV::Tcp _client;
			function<void(Asio::UV::Stream &)> _on_con;
			function<void(Asio::UV::Stream &)> _on_disco;
			function<void(Asio::UV::Stream &, const string &)> _on_data;
	};

	TcpClientTest::TcpClientTest()
		: Asio::UV::Application(), Test(), _server("socat pipe tcp-listen:9080"), _client(Loop(), bind(&TcpClientTest::onConnect, ref(*this), placeholders::_1), bind(&TcpClientTest::onDisconnect, ref(*this), placeholders::_1), bind(&TcpClientTest::onData, ref(*this), placeholders::_1, placeholders::_2), bind(&TcpClientTest::onError, ref(*this), placeholders::_1)), _on_con(), _on_disco(), _on_data()
	{
		// 2016-01-04 AMR FIXME: cleanup
		// 2016-01-04 AMR NOTE: allow 'echo server' to intitialize, 10ms worked on my setup
		usleep(10 * 1000);
	}

	TcpClientTest::~TcpClientTest()
	{
		_server.Term();
	}

	void TcpClientTest::onConnect(Asio::UV::Stream &s)
	{
		if(_on_con)
			_on_con(s);
	}

	void TcpClientTest::onDisconnect(Asio::UV::Stream &s)
	{
		if(_on_disco)
			_on_disco(s);
	}

	void TcpClientTest::onData(Asio::UV::Stream &s, const string &d)
	{
		if(_on_data)
			_on_data(s, d);
	}

	void TcpClientTest::onError(const Exception &e)
	{
		throw e;
	}

	TEST_F(TcpClientTest, Initialize) {
	}

	TEST_F(TcpClientTest, FixtureTestBasicEcho) {
		// 2016-01-04 AMR NOTE: w/o sending at least a newline there will be no read and therefore no disconnect
		Process p("echo -e '42\\n' | socat - tcp:localhost:9080");
		int num;
		p.Out() >> num;
		EXPECT_EQ(42, num);
	}

	TEST_F(TcpClientTest, Connect) {
		TEST_BEGIN
			_on_con = [](auto &s) {
				s.Write("\n");
			};
			_on_data = [](auto &s, auto &) {
				s.Disconnect();
			};

			_client.Connect("localhost", "9080");

			(*this)();
		TEST_END
	}

	TEST_F(TcpClientTest, ReadWrite) {
		TEST_BEGIN
			string data;

			_on_con = [](auto &s) {
				s.Write("Hello World!\n");
			};
			_on_data = [&data](auto &s, auto &d) {
				data = d;
				s.Disconnect();
			};

			_client.Connect("localhost", "9080");

			(*this)();

			EXPECT_EQ(data, "Hello World!\n"s);
		TEST_END
	}

	TEST_F(TcpClientTest, MultiReadWrite) {
		TEST_BEGIN
			string send = "Hello World!\n";
			string total_send;
			string data;
			size_t count = 10000;
			size_t len = 0;

			for(size_t x = 0; x < count; x++)
				total_send += send;

			size_t total_len = total_send.size();

			_on_con = [send, count](auto &s) {
				for(size_t x = 0; x < count; x++)
					s.Write(send);
			};
			_on_data = [&data, &len, total_len](auto &s, auto &d) {
				data += d;
				len += d.size();

				if(len == total_len)
					s.Disconnect();
			};

			_client.Connect("localhost", "9080");

			(*this)();

			EXPECT_EQ(data, total_send);
			EXPECT_EQ(len, total_len);
		TEST_END
	}
}
