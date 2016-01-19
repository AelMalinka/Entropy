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
			function<void()> _what;
			std::string _data;
			std::string _send;
	};

	TcpServerTest::TcpServerTest()
		: Asio::UV::Application(), Test(), _server(Loop(), bind(&TcpServerTest::onConnect, ref(*this), placeholders::_1), bind(&TcpServerTest::onDisconnect, ref(*this), placeholders::_1), bind(&TcpServerTest::onData, ref(*this), placeholders::_1, placeholders::_2), bind(&TcpServerTest::onError, ref(*this), placeholders::_1)), _data(), _send()
	{}

	TcpServerTest::~TcpServerTest()
	{}

	void TcpServerTest::onConnect(Asio::UV::Stream &s)
	{
		s.Write(_send + "\n");
	}

	void TcpServerTest::onDisconnect(Asio::UV::Stream &)
	{
		_server.Disconnect();
	}

	void TcpServerTest::onData(Asio::UV::Stream &, const string &d)
	{
		_data = d;
	}

	void TcpServerTest::onError(const Exception &e)
	{
		throw e;
	}

	TEST_F(TcpServerTest, Initialize) {
	}

	TEST_F(TcpServerTest, Connect) {
		TEST_BEGIN
			_server.Listen("localhost", "9081");
			Process p("echo -e '\n' | socat - tcp:localhost:9081");

			(*this)();

			EXPECT_EQ(p.Return(), 0);
		TEST_END
	}

	TEST_F(TcpServerTest, ReadWrite) {
		TEST_BEGIN
			_send = "And to you too!";
			_server.Listen("localhost", "9081");
			Process p("echo 'Hello World!' | socat - tcp:localhost:9081");

			(*this)();

			string out;
			getline(p.Out(), out);

			EXPECT_EQ(p.Return(), 0);
			EXPECT_EQ(_data, "Hello World!\n"s);
			EXPECT_EQ(out, _send);
		TEST_END
	}
}
