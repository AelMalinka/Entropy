/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "PNG.hh"
#include <gtest/gtest.h>
#include <cstdlib>

using namespace Entropy;
using namespace std;
using namespace testing;

#define TEST_BEGIN try {
#define TEST_END } catch(exception &e) { FAIL() << e << endl; }

namespace {
	string Dir();

	TEST(PNG, Initialize) {
		TEST_BEGIN
			PNG a;
		TEST_END
	}

	TEST(PNG, ReadFile) {
		TEST_BEGIN
			PNG a(Dir() + "pnglogo.png"s);

			EXPECT_EQ(PNG::Red(a[0]), 0x04);
			EXPECT_EQ(PNG::Green(a[0]), 0x02);
			EXPECT_EQ(PNG::Blue(a[0]), 0x04);
			EXPECT_EQ(PNG::Alpha(a[0]), 0xFF);

			EXPECT_EQ(a[0], 0xFF040204);
			EXPECT_EQ(a[a.Width() - 1], 0xFF040204);
			EXPECT_EQ(a[a.Width() * (a.Height() - 1)], 0xFF040204);
			EXPECT_EQ(a[a.Width() * (a.Height() - 1) + a.Width() - 1], 0xFF040204);
		TEST_END
	}

	TEST(PNG, WriteFile) {
		TEST_BEGIN
			PNG a(Dir() + "pnglogo.png"s);
			a.Write("out.png");
			PNG b("out.png");

			auto x = 0;
			for(auto p : a) {
				EXPECT_EQ(p,  b[x++]);
			}
		TEST_END
	}

	string Dir()
	{
		string dir;

		if(getenv("BUILD") == nullptr)
			dir = "./";
		else
			dir = getenv("BUILD") + "/"s;

		return dir;
	}
}
