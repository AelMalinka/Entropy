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
			void onError(const Net::Exception &);
		protected:
			Process _server;
			Asio::UV::Tcp _client;
			std::string _data;
			std::string _send;
	};

	TcpClientTest::TcpClientTest()
		: Asio::UV::Application(), Test(), _server("socat pipe tcp-listen:9080"), _client(Loop(), bind(&TcpClientTest::onConnect, ref(*this), placeholders::_1), bind(&TcpClientTest::onDisconnect, ref(*this), placeholders::_1), bind(&TcpClientTest::onData, ref(*this), placeholders::_1, placeholders::_2), bind(&TcpClientTest::onError, ref(*this), placeholders::_1)), _data(), _send()
	{
		// 2016-01-04 AMR TODO: cleanup
		// 2016-01-04 AMR NOTE: allow 'echo server' to intitialize, 10ms worked on my setup
		usleep(10 * 1000);
	}

	TcpClientTest::~TcpClientTest()
	{
		_server.Term();
	}

	void TcpClientTest::onConnect(Asio::UV::Stream &s)
	{
		s.Write(_send);
	}

	void TcpClientTest::onDisconnect(Asio::UV::Stream &)
	{}

	void TcpClientTest::onData(Asio::UV::Stream &s, const string &d)
	{
		_data = d;
		s.Disconnect();
	}

	void TcpClientTest::onError(const Net::Exception &e)
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
			_send = "\n";

			_client.Connect("localhost", "9080");

			(*this)();
		TEST_END
	}

	TEST_F(TcpClientTest, ReadWrite) {
		TEST_BEGIN
			_send = "Hello World!\n";

			_client.Connect("localhost", "9080");

			(*this)();

			EXPECT_EQ(_data, "Hello World!\n"s);
		TEST_END
	}
}
