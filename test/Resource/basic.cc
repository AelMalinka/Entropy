/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Resource.hh"
#include <gtest/gtest.h>

using namespace Entropy;
using namespace std;
using namespace testing;

#define TEST_BEGIN try {
#define TEST_END } catch(exception &e) { FAIL() << e << endl; }

// 2016-06-01 AMR TODO: test Reference load/free code

namespace {
	TEST(Resource, GetFile) {
		TEST_BEGIN
			auto res = Resource::get("folder/file");
			
			string data(res->data());
			string val = "This is just an ASCII file\nthat is handled through res\n";

			EXPECT_EQ(data, val);
		TEST_END
	}

	TEST(Resource, GetFolder) {
		TEST_BEGIN
			auto folder = Resource::get("folder");
			Resource::Reference file = folder["file"];

			string data(file->data());
			string val = "This is just an ASCII file\nthat is handled through res\n";

			EXPECT_EQ(data, val);
		TEST_END
	}

	TEST(Resource, NonExistant) {
		EXPECT_THROW(Resource::get("this doesn't exist"), Resource::Exception);
		auto folder = Resource::get("folder");
		EXPECT_THROW(folder["this also doesn't exist"], Resource::Exception);
	}
}
