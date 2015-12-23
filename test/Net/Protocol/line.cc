/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Net/Protocol/Line.hh"
#include "Mock.hh"
#include <gtest/gtest.h>

using namespace std;
using namespace Entropy;
using namespace Entropy::Net::Protocol;
using namespace testing;

namespace {
	TEST(Line, Instantiation) {
		MockApplication app;
		Line<MockApplication, int> l(app);
	}

	TEST(Line, Basic) {
		MockApplication app;
		Line<MockApplication, int> l(app);
		int sock = 0;

		EXPECT_CALL(app, onLine(sock, "Hello World!"s))
			.Times(1);

		l.onData(sock, "Hello World!\r\n");
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
		l.onData(sock, "!\r\n");
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

		l.onData(sock, "Hello World!\r\nThis is a message!");
		l.onData(sock, "\r\nBecause Mehf\r\n");
	}

	TEST(Line, Delimiter) {
		MockApplication app;
		Line<MockApplication, int> l1(app, ":");
		Line<MockApplication, int> l2(app, "\r\n");
		Line<MockApplication, int> l3(app, "\r");
		Line<MockApplication, int> l4(app, "\n");
		Line<MockApplication, int> l5(app, "/");
		int sock = 0;

		EXPECT_CALL(app, onLine(sock, "Hello World!"s))
			.Times(5);
		EXPECT_CALL(app, onLine(sock, "This is a Different Delimiter!"s))
			.Times(5);

		l1.onData(sock, "Hello World!:This is a Different Delimiter!:"s);
		l2.onData(sock, "Hello World!\r\nThis is a Different Delimiter!\r\n"s);
		l3.onData(sock, "Hello World!\rThis is a Different Delimiter!\r"s);
		l4.onData(sock, "Hello World!\nThis is a Different Delimiter!\n"s);
		l5.onData(sock, "Hello World!/This is a Different Delimiter!/"s);
	}
}
