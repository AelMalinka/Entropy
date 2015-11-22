/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Python/Object.hh"
#include <gtest/gtest.h>

using namespace Entropy::Python;
using namespace std;

#define TEST_BEGIN try {
#define TEST_END } catch(exception &e) { FAIL() << e << endl; }

namespace {
	TEST(PythonObjectTest, Instantiation) {
		TEST_BEGIN
			Object null;
			Object number(long(42));
			Object other_number(42.5);
			Object str("Hello World!"s);

			string s1 = str;

			EXPECT_TRUE(null.IsNone());
			EXPECT_EQ(static_cast<long>(number), 42);
			EXPECT_EQ(static_cast<double>(other_number), 42.5);
			EXPECT_STREQ(s1.c_str(), "Hello World!");
		TEST_END
	}
}
