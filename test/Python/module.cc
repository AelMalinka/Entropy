/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Python/Module.hh"
#include <gtest/gtest.h>

using namespace Entropy::Python;
using namespace std;

#define TEST_BEGIN try {
#define TEST_END } catch(exception &e) { FAIL() << e << endl; }

namespace {
	TEST(PythonModuleTest, Import) {
		TEST_BEGIN
			Module m("test");
			EXPECT_FALSE(m.IsNone());
		TEST_END
	}

	TEST(PythonModuleTest, Get) {
		TEST_BEGIN
			Module m("test");
			Object f = m.get("function");
			EXPECT_FALSE(f.IsNone());
		TEST_END
	}

	TEST(PythonModuleTest, Run) {
		TEST_BEGIN
			Module m("test");
			ASSERT_FALSE(m.IsNone());
			Object f = m.get("function");
			ASSERT_FALSE(f.IsNone());
			f();
		TEST_END
	}

	TEST(PythonModuleTest, Retrun) {
		TEST_BEGIN
			Module m("test");
			ASSERT_FALSE(m.IsNone());
			Object f = m.get("function");
			ASSERT_FALSE(f.IsNone());
			Object r = f();
			ASSERT_FALSE(r.IsNone());
			EXPECT_EQ(static_cast<long>(r), 12);
		TEST_END
	}
}
