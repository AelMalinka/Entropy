/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_POLYMORPHICLISTITERATOR_INC
#	define ENTROPY_POLYMORPHICLISTITERATOR_INC

#	include <list>
#	include <memory>

	namespace Entropy
	{
		template<typename T>
		class PolymorphicListIterator
		{
			public:
				PolymorphicListIterator(const typename std::list<std::shared_ptr<T>>::iterator &);
				~PolymorphicListIterator();
			public:
				T &operator * ();
				T *operator -> ();
				std::shared_ptr<T> &shared();
				operator std::shared_ptr<T> &();
			public:
				PolymorphicListIterator<T> &operator ++();
				PolymorphicListIterator<T> &operator --();
				PolymorphicListIterator<T> operator ++(int);
				PolymorphicListIterator<T> operator --(int);
				bool operator == (const PolymorphicListIterator<T> &) const;
				bool operator != (const PolymorphicListIterator<T> &) const;
			private:
				typename std::list<std::shared_ptr<T>>::iterator _me;
		};

		template<typename T>
		class PolymorphicListConstIterator
		{
			public:
				PolymorphicListConstIterator(const typename std::list<std::shared_ptr<T>>::const_iterator &);
				~PolymorphicListConstIterator();
			public:
				const T &operator * ();
				const T *operator -> ();
				// 2018-01-10 AMR NOTE: const T * != const shared_ptr<T>
			public:
				PolymorphicListConstIterator<T> &operator ++();
				PolymorphicListConstIterator<T> &operator --();
				PolymorphicListConstIterator<T> operator ++(int);
				PolymorphicListConstIterator<T> operator --(int);
				bool operator == (const PolymorphicListConstIterator<T> &) const;
				bool operator != (const PolymorphicListConstIterator<T> &) const;
			private:
				typename std::list<std::shared_ptr<T>>::const_iterator _me;
		};
	}

#	include "PolymorphicListIterator.impl.hh"

#endif
