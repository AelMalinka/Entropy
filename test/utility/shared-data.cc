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
				explicit shared_data(const int);
				int Data;
			};
	}

	class TestData :
		private SharedData<detail::shared_data>
	{
		public:
			TestData();
			explicit TestData(const int);
			int &Data();
			const int &Data() const;
	};

	TEST(SharedData, Basic) {
		{
			TestData a;
			TestData b;

			TestData c = a;
			TestData d = b;

			TestData e(a);
			TestData f = TestData();

			const TestData g;
			const TestData h(a);
			const TestData i = a;

			EXPECT_EQ(a.Data(), b.Data());
			EXPECT_EQ(a.Data(), c.Data());
			EXPECT_EQ(a.Data(), d.Data());
			EXPECT_EQ(a.Data(), e.Data());
			EXPECT_EQ(a.Data(), f.Data());
			EXPECT_EQ(a.Data(), g.Data());
			EXPECT_EQ(a.Data(), h.Data());
			EXPECT_EQ(a.Data(), i.Data());

			a.Data() = 20;

			EXPECT_EQ(a.Data(), b.Data());
			EXPECT_EQ(a.Data(), c.Data());
			EXPECT_EQ(a.Data(), d.Data());
			EXPECT_EQ(a.Data(), e.Data());
			EXPECT_EQ(a.Data(), f.Data());
			EXPECT_EQ(a.Data(), g.Data());
			EXPECT_EQ(a.Data(), h.Data());
			EXPECT_EQ(a.Data(), i.Data());

			b.Data() = 30;

			EXPECT_EQ(a.Data(), b.Data());
			EXPECT_EQ(a.Data(), c.Data());
			EXPECT_EQ(a.Data(), d.Data());
			EXPECT_EQ(a.Data(), e.Data());
			EXPECT_EQ(a.Data(), f.Data());
			EXPECT_EQ(a.Data(), g.Data());
			EXPECT_EQ(a.Data(), h.Data());
			EXPECT_EQ(a.Data(), i.Data());
		}

		TestData a;
		EXPECT_EQ(a.Data(), 10);
	}

	TEST(SharedData, WithConstructor) {
		TestData a(20);
		TestData b(30);

		EXPECT_EQ(a.Data(), 20);
		EXPECT_EQ(b.Data(), 20);
	}

	TestData::TestData()
		: SharedData<detail::shared_data>()
	{}

	TestData::TestData(const int val)
		: SharedData<detail::shared_data>(val)
	{}

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

	detail::shared_data::shared_data(const int val)
		: Data(val)
	{}
}
