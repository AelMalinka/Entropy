/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_DEFAULTEDLIST_INC
#	define ENTROPY_DEFAULTEDLIST_INC

#	include "Exception.hh"
#	include <list>
#	include <initializer_list>
#	include <utility>
#	include <iterator>

	namespace Entropy
	{
		ENTROPY_EXCEPTION_BASE(DefaultedListException, "DefaultedList Exception");

		template<typename T>
		class DefaultedList
		{
			public:
				template<typename ...Args>
				explicit DefaultedList(Args && ...);
				explicit DefaultedList(const T &);
				explicit DefaultedList(T &&);
				DefaultedList(std::initializer_list<T>);
				DefaultedList(const DefaultedList<T> &);
				DefaultedList(DefaultedList<T> &&);
				~DefaultedList();
			public:
				typedef typename std::list<T>::iterator iterator;
				typedef typename std::list<T>::const_iterator const_iterator;
			public:
				T &get();
				T &operator * ();
				T *operator -> ();
				const T &get() const;
				const T &operator * () const;
				const T *operator -> () const;
				void setDefault(const iterator &);
				void setDefault(const const_iterator &);
			public:
				T &front();
				T &back();
				iterator begin();
				iterator end();
				T &operator [] (const std::size_t &);
				const T &front() const;
				const T &back() const;
				const_iterator begin() const;
				const_iterator end() const;
				const T &operator [] (const std::size_t &) const;
				std::size_t size() const;
			public:
				void push_front(const T &);
				void push_front(T &&);
				template<typename ...Args>
				void emplace_front(Args && ...);
				void push_back(const T &);
				void push_back(T &&);
				template<typename ...Args>
				void emplace_back(Args && ...);
				template<typename ...Args>
				void clear(Args && ...);
				void erase(const iterator &);
			private:
				std::list<T> _list;
				iterator _default;
		};
	}

#	include "DefaultedList.impl.hh"

#endif
