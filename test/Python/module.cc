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
			Object f = m.get("first");
			EXPECT_FALSE(f.IsNone());
		TEST_END
	}

	TEST(PythonModuleTest, Run) {
		TEST_BEGIN
			Module m("test");
			Object f = m.get("first");
			f();
		TEST_END
	}

	TEST(PythonModuleTest, Retrun) {
		TEST_BEGIN
			Module m("test");
			Object f = m.get("first");
			Object r = f();
			EXPECT_EQ(static_cast<long>(r), 12);
		TEST_END
	}

	TEST(PythonModuleTest, RunParamLong) {
		TEST_BEGIN
			Module m("test");
			Object f = m.get("second");
			long v = 13;
			long r = f(v);
			EXPECT_FLOAT_EQ(r, v);
		TEST_END
	}

	TEST(PythonModuleTest, RunParamFloat) {
		TEST_BEGIN
			Module m("test");
			Object f = m.get("second");
			double v = 15.5;
			double r = f(v);
			EXPECT_FLOAT_EQ(r, v);
		TEST_END
	}

	TEST(PythonModuleTest, RunParamString) {
		TEST_BEGIN
			Module m("test");
			Object f = m.get("second");
			string v = "Hello World!";
			string r = f("Hello World!");
			EXPECT_EQ(r, v);
		TEST_END
	}
}
