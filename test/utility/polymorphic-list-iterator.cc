/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "PolymorphicListIterator.hh"
#include <gtest/gtest.h>

using namespace Entropy;
using namespace testing;
using namespace std;

namespace {
	class A
	{
		public:
			virtual int Value() = 0;
			virtual int Value() const = 0;
	};

	class B :
		public A
	{
		int Value();
		int Value() const;
	};

	class C :
		public A
	{
		int Value();
		int Value() const;
	};

	TEST(PolymorphicListIterator, Constructors) {
		list<shared_ptr<A>> t;

		t.push_back(make_shared<B>());
		t.push_back(make_shared<C>());

		PolymorphicListIterator<A> a = t.begin();
		PolymorphicListIterator<A> b = ++t.begin();
		PolymorphicListIterator<A> c = t.end();

		EXPECT_EQ(a, t.begin());
		EXPECT_EQ(b, ++t.begin());
		EXPECT_EQ(c, t.end());

		EXPECT_NE(a, b);
		EXPECT_NE(a, c);

		EXPECT_NE(b, a);
		EXPECT_NE(b, c);

		EXPECT_NE(c, a);
		EXPECT_NE(c, b);
	}

	TEST(PolymorphicListIterator, Accessors) {
		list<shared_ptr<A>> t;

		t.push_back(make_shared<B>());
		t.push_back(make_shared<C>());

		PolymorphicListIterator<A> a = t.begin();
		PolymorphicListIterator<A> b = ++t.begin();

		EXPECT_EQ((*a).Value(), 10);
		EXPECT_EQ(a->Value(), 10);
		EXPECT_EQ(a.shared()->Value(), 10);

		EXPECT_EQ((*b).Value(), 20);
		EXPECT_EQ(b->Value(), 20);
		EXPECT_EQ(b.shared()->Value(), 20);


		EXPECT_NE((*a).Value(), 20);
		EXPECT_NE(a->Value(), 20);
		EXPECT_NE(a.shared()->Value(), 20);


		EXPECT_NE((*b).Value(), 10);
		EXPECT_NE(b->Value(), 10);
		EXPECT_NE(b.shared()->Value(), 10);

		shared_ptr<A> e = a;
		shared_ptr<A> f = b;

		EXPECT_EQ(e->Value(), 10);
		EXPECT_EQ(f->Value(), 20);

		PolymorphicListConstIterator<A> c = t.cbegin();
		PolymorphicListConstIterator<A> d = ++t.cbegin();

		EXPECT_EQ((*c).Value(), 15);
		EXPECT_EQ(c->Value(), 15);

		EXPECT_EQ((*d).Value(), 25);
		EXPECT_EQ(d->Value(), 25);

		EXPECT_NE((*c).Value(), 25);
		EXPECT_NE(c->Value(), 25);

		EXPECT_NE((*d).Value(), 15);
		EXPECT_NE(d->Value(), 15);
	}

	TEST(PolymorphicIterator, Iterate) {
		list<shared_ptr<A>> t;

		t.push_back(make_shared<B>());
		t.push_back(make_shared<B>());

		for(PolymorphicListIterator<A> a = t.begin(); a != t.end(); a++) {
			EXPECT_EQ(a->Value(), 10);
		}

		for(PolymorphicListConstIterator<A> a = t.cbegin(); a != t.cend(); a++) {
			EXPECT_EQ(a->Value(), 15);
		}

		t.clear();
		t.push_back(make_shared<C>());
		t.push_back(make_shared<C>());

		for(PolymorphicListIterator<A> a = t.begin(); a != t.end(); a++) {
			EXPECT_EQ(a->Value(), 20);
		}

		for(PolymorphicListConstIterator<A> a = t.cbegin(); a != t.cend(); a++) {
			EXPECT_EQ(a->Value(), 25);
		}
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
