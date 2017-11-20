/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "DefaultedList.hh"
#include <gtest/gtest.h>

using namespace Entropy;
using namespace testing;
using namespace std;

namespace {
	class Item
	{
		public:
			Item();
			Item(const int);
			Item(const int, const string &);
			operator int() const;
			const int &Value() const;
			bool hasString() const;
		private:
			int _value;
			bool _string;
	};

	TEST(DefaultedList, Construct) {
		const Item t(5);

		DefaultedList<Item> a;
		DefaultedList<Item> b(10);
		DefaultedList<Item> c = {
			20,
			10,
			5
		};
		DefaultedList<Item> d(t);
		DefaultedList<Item> e(Item(15));
		DefaultedList<Item> f = a;
		DefaultedList<Item> g = DefaultedList<Item>();

		EXPECT_EQ(a.get(), 0);
		EXPECT_EQ(*b, 10);
		EXPECT_EQ(c->Value(), 20);
		EXPECT_EQ(d.front(), 5);
		EXPECT_EQ(e.begin()->Value(), 15);
		EXPECT_EQ(f.get(), 0);
		EXPECT_EQ(g.get(), 0);
	}

	TEST(DefaultedList, StaysDefault) {
		DefaultedList<Item> a(5);

		a.emplace_back(10);
		EXPECT_EQ(*a, 5);
		a.push_back(Item(10));
		EXPECT_EQ(*a, 5);
		a.emplace_front(10);
		EXPECT_EQ(*a, 5);
		a.push_front(10);
		EXPECT_EQ(*a, 5);
		a.erase(a.begin());
		a.erase(a.begin());
		EXPECT_EQ(*a, 5);
		a.erase(--a.end());
		a.erase(--a.end());
		EXPECT_EQ(*a, 5);
	}

	TEST(DefaultedList, SetDefault) {
		DefaultedList<Item> a;
		a.push_back(10);
		auto i = a.current();

		EXPECT_EQ(*a, 0);
		EXPECT_EQ(a.current(), i);
		EXPECT_EQ(*i, 0);

		auto j = --a.end();
		a.setDefault(j);
		EXPECT_EQ(*a, 10);
		EXPECT_EQ(j, a.current());
		EXPECT_NE(i, j);
	}

	TEST(DefaultedList, MultipleConstructor) {
		DefaultedList<Item> a(5, "Hello!"s);

		a.emplace_back(10, "Goodbye!"s);
		a.emplace_front(10, "Do I know you?"s);

		EXPECT_EQ(a.size(), 3ul);
		for(auto &&i : a) {
			EXPECT_TRUE(i.hasString());
		}

		EXPECT_EQ(*a, 5);
	}

	TEST(DefaultedList, RemoveDefault) {
		DefaultedList<Item> a(5);

		EXPECT_THROW(a.erase(a.begin()), Exception);
		a.clear();
		EXPECT_EQ(*a, 0);
		EXPECT_EQ(a.size(), 1ul);
	}

	Item::Item()
		: _value(0), _string(false)
	{}

	Item::Item(const int v)
		: _value(v), _string(false)
	{}

	Item::Item(const int v, const string &)
		: _value(v), _string(true)
	{}

	Item::operator int() const
	{
		return Value();
	}

	const int &Item::Value() const
	{
		return _value;
	}

	bool Item::hasString() const
	{
		return _string;
	}
}
