/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Process.hh"
#include <gtest/gtest.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <boost/lexical_cast.hpp>

using namespace Entropy;
using namespace std;
using namespace testing;

using boost::lexical_cast;

#define TEST_BEGIN try {
#define TEST_END } catch(exception &e) { FAIL() << e << endl; }

namespace {
	TEST(Process, Create) {
		TEST_BEGIN
			Process p([](){
			});
			EXPECT_EQ(p.Return(), 0);
		TEST_END
	}

	TEST(Process, Exit) {
		TEST_BEGIN
			Process p1([](){
			});
			Process p2([](){
				exit(10);
			});

			EXPECT_EQ(p1.Return(), 0);
			EXPECT_EQ(p2.Return(), 10);
		TEST_END
	}

	TEST(Process, Kill) {
		TEST_BEGIN
			Process p([](){while(true);});
			p.Term();
		TEST_END
	}

	TEST(Process, ReadWrite) {
		TEST_BEGIN
			Process p([](){
				int val;
				cin >> val;
				cout << "value: " << val << endl;
			});
			p.In() << 42 << endl;
			EXPECT_EQ(p.Return(), 0);
			string line;
			getline(p.Out(), line);
			EXPECT_EQ(line, "value: 42"s);
		TEST_END
	}

	TEST(Process, Error) {
		TEST_BEGIN
			Process p([](){
				cerr << "this is an error output" << endl;
			});
			EXPECT_EQ(p.Return(), 0);
			string line;
			getline(p.Error(), line);
			EXPECT_EQ(line, "this is an error output"s);
		TEST_END
	}

	TEST(Process, NonZeroExit) {
		TEST_BEGIN
			Process p([](){
				exit(129);
			});
			EXPECT_EQ(p.Return(), 129);
		TEST_END
	}

	TEST(Process, System) {
		TEST_BEGIN
			Process p("echo \"this is another test\"");
			EXPECT_EQ(p.Return(), 0);
			string line;
			getline(p.Out(), line);
			EXPECT_EQ(line, "this is another test"s);
		TEST_END
	}
}
