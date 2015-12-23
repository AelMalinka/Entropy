/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include PROTOCOL_INCLUDE
#include "Mock.hh"
#include <gtest/gtest.h>

using namespace std;
using namespace Entropy;
using namespace Entropy::Net::Protocol;
using namespace testing;

namespace {
	TEST(PROTOCOL, Instantiation) {
		MOCK_FULL app;
		PROTOCOL<MOCK_FULL, int> l(app);
	}

	TEST(PROTOCOL, onConnect) {
		MOCK_FULL app;
		PROTOCOL<MOCK_FULL, int> l(app);
		int sock = 0;

		EXPECT_CALL(app, onConnect(_))
			.Times(1);

		l.onConnect(sock);
	}

	TEST(PROTOCOL, onConnectNoConnect) {
		StrictMock<MOCK_BASE> app;
		PROTOCOL<MOCK_BASE, int> l(app);
		int sock = 0;

		l.onConnect(sock);
	}

	TEST(PROTOCOL, onDisconnect) {
		MOCK_FULL app;
		PROTOCOL<MOCK_FULL, int> l(app);
		int sock = 0;

		EXPECT_CALL(app, onDisconnect(_))
			.Times(1);

		l.onDisconnect(sock);
	}

	TEST(PROTOCOL, onDisconnectNoDisconnect) {
		StrictMock<MOCK_BASE> app;
		PROTOCOL<MOCK_BASE, int> l(app);
		int sock = 0;

		l.onDisconnect(sock);
	}

	TEST(PROTOCOL, onError) {
		MOCK_FULL app;
		PROTOCOL<MOCK_FULL, int> l(app);
		Net::Exception err("This is an error");

		EXPECT_CALL(app, onError(_))
			.Times(1);

		l.onError(err);
	}

	TEST(PROTOCOL, onErrorNoError) {
		StrictMock<MOCK_BASE> app;
		PROTOCOL<MOCK_BASE, int> l(app);
		Net::Exception err("This is an error");

		EXPECT_THROW(l.onError(err), Net::Exception);
	}
}
