/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_TEST_NET_PROTOCOL_MOCK_INC
#	define ENTROPY_TEST_NET_PROTOCOL_MOCK_INC

#	include "Net/Protocol/Line.hh"
#	include <gmock/gmock.h>

	namespace {
		class MockApplication {
			public:
				MOCK_METHOD1(onConnect, void(int &));
				MOCK_METHOD1(onDisconnect, void(int &));
				MOCK_METHOD1(onError, void(const Entropy::Net::Exception &));
				MOCK_METHOD2(onLine, void(int &, const std::string &));
		};

		class MockApplicationOnlyLine {
			public:
				MOCK_METHOD2(onLine, void(int &, const std::string &));
		};
	}

#endif
