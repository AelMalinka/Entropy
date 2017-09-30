/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_POLYMORPHICLIST_INC
#	define ENTROPY_POLYMORPHICLIST_INC

#	include "PolymorphicListIterator.hh"
#	include <type_traits>

	namespace Entropy
	{
		template<typename T>
		class PolymorphicList
		{
			public:
				PolymorphicList();
				PolymorphicList(const PolymorphicList<T> &);
				PolymorphicList(PolymorphicList<T> &&);
				~PolymorphicList();
			public:
				void clear();
				void push_front(const std::shared_ptr<T> &);
				template<typename U, typename = typename std::enable_if<std::is_base_of<T, U>::value>::type>
				void push_front(U &&);
				void push_front(T *);
				template<typename U, typename ...Args>
				void emplace_front(Args && ...);
				void push_back(const std::shared_ptr<T> &);
				template<typename U, typename = typename std::enable_if<std::is_base_of<T, U>::value>::type>
				void push_back(U &&);
				void push_back(T *);
				template<typename U, typename ...Args>
				void emplace_back(Args && ...);
			public:
				typedef PolymorphicListIterator<T> iterator;
				typedef PolymorphicListConstIterator<T> const_iterator;
			public:
				std::size_t size() const;
				iterator begin();
				iterator end();
				const_iterator begin() const;
				const_iterator end() const;
				T &front();
				T &back();
				const T &front() const;
				const T &back() const;
				T &operator [] (const std::size_t &);
				const T &operator [] (const std::size_t &) const;
			private:
				std::list<std::shared_ptr<T>> _list;
		};
	}

#	include "PolymorphicList.impl.hh"

#endif
