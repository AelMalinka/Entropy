/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "SharedData.hh"

using namespace std;
using namespace testing;
using namespace Entropy;

namespace {
	namespace detail {
			struct shared_data
			{
				shared_data();
				int Data;
			};
	}

	class TestData :
		private SharedData<detail::shared_data>
	{
		public:
			int &Data();
			const int &Data() const;
		private:
	};

	TEST(SharedData, Basic) {
		{
			TestData a;
			TestData b;

			EXPECT_EQ(a.Data(), b.Data());

			a.Data() = 20;

			EXPECT_EQ(a.Data(), b.Data());

			b.Data() = 30;

			EXPECT_EQ(a.Data(), b.Data());
		}

		TestData a;
		EXPECT_EQ(a.Data(), 10);
	}

	int &TestData::Data()
	{
		return shared()->Data;
	}

	const int &TestData::Data() const
	{
		return shared()->Data;
	}

	detail::shared_data::shared_data()
		: Data(10)
	{}
}
