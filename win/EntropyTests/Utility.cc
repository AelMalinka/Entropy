/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Tests
{
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

	namespace detail {
		struct shared_data
		{
			shared_data();
			explicit shared_data(const int);
			int Data;
		};
	}

	class TestData :
		private Entropy::SharedData<detail::shared_data>
	{
		public:
			TestData();
			explicit TestData(const int);
			int &Data();
			const int &Data() const;
	};

	TEST_CLASS(DefaultedList)
	{
		TEST_METHOD(Construct)
		{
			const Item t(5);

			Entropy::DefaultedList<Item> a;
			Entropy::DefaultedList<Item> b(10);
			Entropy::DefaultedList<Item> c = {
				20,
				10,
				5
			};
			Entropy::DefaultedList<Item> d(t);
			Entropy::DefaultedList<Item> e(Item(15));
			Entropy::DefaultedList<Item> f = a;
			Entropy::DefaultedList<Item> g = Entropy::DefaultedList<Item>();

			Assert::AreEqual(a.get().Value(), 0);
			Assert::AreEqual((int)*b, 10);
			Assert::AreEqual(c->Value(), 20);
			Assert::AreEqual(d.front().Value(), 5);
			Assert::AreEqual(e.begin()->Value(), 15);
			Assert::AreEqual(f->Value(), 0);
			Assert::AreEqual(g->Value(), 0);
		}

		TEST_METHOD(StaysDefault)
		{
			Entropy::DefaultedList<Item> a(5);

			a.emplace_back(10);
			Assert::AreEqual(a->Value(), 5);
			a.push_back(Item(10));
			Assert::AreEqual(a->Value(), 5);
			a.emplace_front(10);
			Assert::AreEqual(a->Value(), 5);
			a.push_front(10);
			Assert::AreEqual(a->Value(), 5);
			a.erase(a.begin());
			a.erase(a.begin());
			Assert::AreEqual(a->Value(), 5);
			a.erase(--a.end());
			a.erase(--a.end());
			Assert::AreEqual(a->Value(), 5);
		}

		TEST_METHOD(MultipleConstructor) {
			Entropy::DefaultedList<Item> a(5, "Hello!"s);

			a.emplace_back(10, "Goodbye!"s);
			a.emplace_front(10, "Do I know you?"s);

			Assert::AreEqual(a.size(), 3u);
			for (auto &&i : a) {
				Assert::IsTrue(i.hasString());
			}

			Assert::AreEqual(a->Value(), 5);
		}

		TEST_METHOD(RemoveDefault) {
			Entropy::DefaultedList<Item> a(5);

			Assert::ExpectException<Entropy::DefaultedListException>([&]() { a.erase(a.begin()); });
			a.clear();
			Assert::AreEqual(a->Value(), 0);
			Assert::AreEqual(a.size(), 1u);
		}
	};

	TEST_CLASS(PolymorphicList) {
		TEST_METHOD(IteratorConstructors) {
			using Entropy::PolymorphicListIterator;

			list<shared_ptr<A>> t;

			t.push_back(make_shared<B>());
			t.push_back(make_shared<C>());

			PolymorphicListIterator<A> a = t.begin();
			PolymorphicListIterator<A> b = ++t.begin();
			PolymorphicListIterator<A> c = t.end();

			Assert::IsTrue(a == t.begin());
			Assert::IsTrue(b == ++t.begin());
			Assert::IsTrue(c == t.end());

			Assert::IsFalse(a == b);
			Assert::IsFalse(a == c);

			Assert::IsFalse(b == a);
			Assert::IsFalse(b == c);

			Assert::IsFalse(c == a);
			Assert::IsFalse(c == b);
		}

		TEST_METHOD(IteratorAccessors) {
			using Entropy::PolymorphicListIterator;
			using Entropy::PolymorphicListConstIterator;

			list<shared_ptr<A>> t;

			t.push_back(make_shared<B>());
			t.push_back(make_shared<C>());

			PolymorphicListIterator<A> a = t.begin();
			PolymorphicListIterator<A> b = ++t.begin();

			Assert::AreEqual((*a).Value(), 10);
			Assert::AreEqual(a->Value(), 10);

			Assert::AreEqual((*b).Value(), 20);
			Assert::AreEqual(b->Value(), 20);

			Assert::AreNotEqual((*a).Value(), 20);
			Assert::AreNotEqual(a->Value(), 20);

			Assert::AreNotEqual((*b).Value(), 10);
			Assert::AreNotEqual(b->Value(), 10);

			PolymorphicListConstIterator<A> c = t.cbegin();
			PolymorphicListConstIterator<A> d = ++t.cbegin();

			Assert::AreEqual((*c).Value(), 15);
			Assert::AreEqual(c->Value(), 15);

			Assert::AreEqual((*d).Value(), 25);
			Assert::AreEqual(d->Value(), 25);

			Assert::AreNotEqual((*c).Value(), 25);
			Assert::AreNotEqual(c->Value(), 25);

			Assert::AreNotEqual((*d).Value(), 15);
			Assert::AreNotEqual(d->Value(), 15);
		}

		TEST_METHOD(IteratorIterate) {
			using Entropy::PolymorphicListIterator;
			using Entropy::PolymorphicListConstIterator;

			list<shared_ptr<A>> t;

			t.push_back(make_shared<B>());
			t.push_back(make_shared<B>());

			for (PolymorphicListIterator<A> a = t.begin(); a != t.end(); a++) {
				Assert::AreEqual(a->Value(), 10);
			}

			for (PolymorphicListConstIterator<A> a = t.cbegin(); a != t.cend(); a++) {
				Assert::AreEqual(a->Value(), 15);
			}

			t.clear();
			t.push_back(make_shared<C>());
			t.push_back(make_shared<C>());

			for (PolymorphicListIterator<A> a = t.begin(); a != t.end(); a++) {
				Assert::AreEqual(a->Value(), 20);
			}

			for (PolymorphicListConstIterator<A> a = t.cbegin(); a != t.cend(); a++) {
				Assert::AreEqual(a->Value(), 25);
			}
		}

		TEST_METHOD(Constructors) {
			using Entropy::PolymorphicList;

			PolymorphicList<A> a;
			PolymorphicList<A> b = a;
			PolymorphicList<A> c = PolymorphicList<A>();

			Assert::AreEqual(a.size(), 0u);
			Assert::AreEqual(b.size(), 0u);
			Assert::AreEqual(c.size(), 0u);
		}

		TEST_METHOD(Emplace) {
			using Entropy::PolymorphicList;

			PolymorphicList<A> t;

			t.emplace_back<B>();
			t.emplace_back<C>();

			Assert::AreEqual(t.size(), 2u);

			t.emplace_front<B>();
			t.emplace_front<C>();

			Assert::AreEqual(t.size(), 4u);

			t.clear();
			Assert::AreEqual(t.size(), 0u);
		}

		TEST_METHOD(SharedPtr) {
			using Entropy::PolymorphicList;

			PolymorphicList<A> t;

			t.push_back(make_shared<B>());
			t.push_back(make_shared<C>());

			Assert::AreEqual(t.size(), 2u);

			t.push_front(make_shared<B>());
			t.push_front(make_shared<C>());

			Assert::AreEqual(t.size(), 4u);

			t.clear();
			Assert::AreEqual(t.size(), 0u);
		}

		TEST_METHOD(Temporaries) {
			using Entropy::PolymorphicList;

			PolymorphicList<A> t;

			t.push_back(B());
			t.push_back(C());

			Assert::AreEqual(t.size(), 2u);

			t.push_front(B());
			t.push_front(C());

			Assert::AreEqual(t.size(), 4u);

			t.clear();
			Assert::AreEqual(t.size(), 0u);
		}

		TEST_METHOD(Pointers) {
			using Entropy::PolymorphicList;

			PolymorphicList<A> t;

			t.push_back(B());
			t.push_back(C());

			Assert::AreEqual(t.size(), 2u);

			t.push_front(B());
			t.push_front(C());

			Assert::AreEqual(t.size(), 4u);

			t.clear();
			Assert::AreEqual(t.size(), 0u);
		}

		TEST_METHOD(Iterate) {
			using Entropy::PolymorphicList;

			PolymorphicList<A> t;

			t.emplace_back<B>();
			t.push_back(new B);
			t.push_back(B());
			t.push_back(make_shared<B>());

			for (auto &&i : t) {
				Assert::AreEqual(i.Value(), 10);
			}

			const PolymorphicList<A> t1 = t;

			for (auto &&i : t1) {
				Assert::AreEqual(i.Value(), 15);
			}

			t.clear();

			t.emplace_back<C>();
			t.push_back(new C);
			t.push_back(C());
			t.push_back(make_shared<C>());

			for (auto &&i : t) {
				Assert::AreEqual(i.Value(), 20);
			}

			const PolymorphicList<A> t2 = t;

			for (auto &&i : t2) {
				Assert::AreEqual(i.Value(), 25);
			}

			t.clear();

			Assert::AreEqual(t.size(), 0u);
		}

		TEST_METHOD(FrontBack) {
			using Entropy::PolymorphicList;

			PolymorphicList<A> t;

			t.emplace_back<B>();
			t.emplace_back<C>();

			Assert::AreEqual(t.front().Value(), 10);
			Assert::AreEqual(t.back().Value(), 20);

			const PolymorphicList<A> t2 = t;

			Assert::AreEqual(t2.front().Value(), 15);
			Assert::AreEqual(t2.back().Value(), 25);
		}
	};

	TEST_CLASS(SharedData) {
		TEST_METHOD(Basic) {
			{
				TestData a;
				TestData b;

				Assert::AreEqual(a.Data(), b.Data());

				a.Data() = 20;

				Assert::AreEqual(a.Data(), b.Data());

				b.Data() = 30;

				Assert::AreEqual(a.Data(), b.Data());
			}

			TestData a;
			Assert::AreEqual(a.Data(), 10);
		}

		TEST_METHOD(WithConstructor) {
			TestData a(20);
			TestData b(30);

			Assert::AreEqual(a.Data(), 20);
			Assert::AreEqual(b.Data(), 20);
		}
	};

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