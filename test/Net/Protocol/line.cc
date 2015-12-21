/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Net/Protocol/Line.hh"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;
using namespace Entropy;
using namespace Entropy::Net::Protocol;
using namespace testing;

namespace {
	class MockApplication {
		public:
			MOCK_METHOD1(onConnect, void(int &sock));
			MOCK_METHOD1(onError, void(const Net::Exception &error));
			MOCK_METHOD2(onLine, void(int &sock, const string &msg));
	};

	class MockApplicationOnlyMessage {
		public:
			MOCK_METHOD2(onLine, void(int &sock, const string &msg));
	};

	TEST(Line, Instantiation) {
		MockApplication app;
		Line<MockApplication, int> l(app);
	}

	TEST(Line, onConnect) {
		MockApplication app;
		Line<MockApplication, int> l(app);
		int sock = 0;

		EXPECT_CALL(app, onConnect(_))
			.Times(1);

		l.onConnect(sock);
	}

	TEST(Line, onConnectNoConnect) {
		StrictMock<MockApplicationOnlyMessage> app;
		Line<MockApplicationOnlyMessage, int> l(app);
		int sock = 0;

		l.onConnect(sock);
	}

	TEST(Line, onError) {
		MockApplication app;
		Line<MockApplication, int> l(app);
		Net::Exception err("This is an error");

		EXPECT_CALL(app, onError(_))
			.Times(1);

		l.onError(err);
	}

	TEST(Line, onErrorNoError) {
		StrictMock<MockApplicationOnlyMessage> app;
		Line<MockApplicationOnlyMessage, int> l(app);
		Net::Exception err("This is an error");

		EXPECT_THROW(l.onError(err), Net::Exception);
	}

	TEST(Line, Basic) {
		MockApplication app;
		Line<MockApplication, int> l(app);
		int sock = 0;

		EXPECT_CALL(app, onLine(sock, "Hello World!"s))
			.Times(1);

		l.onData(sock, "Hello World!\n");
	}

	TEST(Line, SmallBuffer) {
		MockApplication app;
		Line<MockApplication, int> l(app);
		int sock = 0;

		EXPECT_CALL(app, onLine(sock, "Hello World!"s))
			.Times(1);

		l.onData(sock, "Hello");
		l.onData(sock, " ");
		l.onData(sock, "World");
		l.onData(sock, "!\n");
	}

	TEST(Line, MultipleLines) {
		MockApplication app;
		Line<MockApplication, int> l(app);
		int sock = 0;

		EXPECT_CALL(app, onLine(sock, "Hello World!"s))
			.Times(1);
		EXPECT_CALL(app, onLine(sock, "This is a message!"s))
			.Times(1);
		EXPECT_CALL(app, onLine(sock, "Because Mehf"s))
			.Times(1);

		l.onData(sock, "Hello World!\nThis is a message!");
		l.onData(sock, "\nBecause Mehf\n");
	}

	TEST(Line, Delimiter) {
		MockApplication app;
		Line<MockApplication, int> l1(app, ":");
		Line<MockApplication, int> l2(app, "\r\n");
		Line<MockApplication, int> l3(app, "\r");
		Line<MockApplication, int> l4(app, "/");
		int sock = 0;

		EXPECT_CALL(app, onLine(sock, "Hello World!"s))
			.Times(4);
		EXPECT_CALL(app, onLine(sock, "This is a Different Delimiter!"s))
			.Times(4);

		l1.onData(sock, "Hello World!:This is a Different Delimiter!:"s);
		l2.onData(sock, "Hello World!\r\nThis is a Different Delimiter!\r\n"s);
		l3.onData(sock, "Hello World!\rThis is a Different Delimiter!\r"s);
		l4.onData(sock, "Hello World!/This is a Different Delimiter!/"s);
	}
}
