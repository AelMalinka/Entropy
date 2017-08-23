/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Event.hh"
#include <gtest/gtest.h>

using namespace std;
using namespace Entropy;
using namespace testing;

namespace {
	TEST(Event, Construct) {
		Event e(10ul);

		EXPECT_EQ(e.Id(), 10ul);
	}
}
