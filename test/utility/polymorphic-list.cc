/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "PolymorphicList.hh"
#include <gtest/gtest.h>

using namespace Entropy;
using namespace testing;
using namespace std;

namespace {
	class A
	{
		public:
			virtual int Value() const = 0;
			virtual int Value() = 0;
	};

	class B :
		public A
	{
		int Value() const;
		int Value();
	};

	class C :
		public A
	{
		int Value() const;
		int Value();
	};

	TEST(PolymorphicList, Constructors) {
		PolymorphicList<A> a;
		PolymorphicList<A> b = a;
		PolymorphicList<A> c = PolymorphicList<A>();

		EXPECT_EQ(a.size(), 0ul);
		EXPECT_EQ(b.size(), 0ul);
		EXPECT_EQ(c.size(), 0ul);
	}

	TEST(PolymorphicList, Emplace) {
		PolymorphicList<A> t;

		t.emplace_back<B>();
		t.emplace_back<C>();

		EXPECT_EQ(t.size(), 2ul);

		t.emplace_front<B>();
		t.emplace_front<C>();

		EXPECT_EQ(t.size(), 4ul);

		t.clear();
		EXPECT_EQ(t.size(), 0ul);
	}

	TEST(PolymorphicList, SharedPtr) {
		PolymorphicList<A> t;

		t.push_back(make_shared<B>());
		t.push_back(make_shared<C>());

		EXPECT_EQ(t.size(), 2ul);

		t.push_front(make_shared<B>());
		t.push_front(make_shared<C>());

		EXPECT_EQ(t.size(), 4ul);

		t.clear();
		EXPECT_EQ(t.size(), 0ul);
	}

	TEST(PolymorphicList, Temporaries) {
		PolymorphicList<A> t;

		t.push_back(B());
		t.push_back(C());

		EXPECT_EQ(t.size(), 2ul);

		t.push_front(B());
		t.push_front(C());

		EXPECT_EQ(t.size(), 4ul);

		t.clear();
		EXPECT_EQ(t.size(), 0ul);
	}

	TEST(PolymorphicList, Pointers) {
		PolymorphicList<A> t;

		t.push_back(B());
		t.push_back(C());

		EXPECT_EQ(t.size(), 2ul);

		t.push_front(B());
		t.push_front(C());

		EXPECT_EQ(t.size(), 4ul);

		t.clear();
		EXPECT_EQ(t.size(), 0ul);
	}

	TEST(PolymorphicList, Iterate) {
		PolymorphicList<A> t;

		t.emplace_back<B>();
		t.push_back(new B);
		t.push_back(B());
		t.push_back(make_shared<B>());

		for(auto &&i : t) {
			EXPECT_EQ(i.Value(), 10);
		}

		const PolymorphicList<A> t1 = t;

		for(auto &&i : t1) {
			EXPECT_EQ(i.Value(), 15);
		}

		t.clear();

		t.emplace_back<C>();
		t.push_back(new C);
		t.push_back(C());
		t.push_back(make_shared<C>());

		for(auto &&i : t) {
			EXPECT_EQ(i.Value(), 20);
		}

		const PolymorphicList<A> t2 = t;

		for(auto &&i : t2) {
			EXPECT_EQ(i.Value(), 25);
		}

		t.clear();

		EXPECT_EQ(t.size(), 0ul);
	}

	TEST(PolymorphicList, FrontBack) {
		PolymorphicList<A> t;

		t.emplace_back<B>();
		t.emplace_back<C>();

		EXPECT_EQ(t.front().Value(), 10);
		EXPECT_EQ(t.back().Value(), 20);

		const PolymorphicList<A> t2 = t;

		EXPECT_EQ(t2.front().Value(), 15);
		EXPECT_EQ(t2.back().Value(), 25);
	}

	int B::Value()
	{
		return 10;
	}

	int B::Value() const
	{
		return 15;
	}

	int C::Value()
	{
		return 20;
	}

	int C::Value() const
	{
		return 25;
	}
}
