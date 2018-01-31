/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_POLYMORPHICLISTITERATOR_IMPL
#	define ENTROPY_POLYMORPHICLISTITERATOR_IMPL

#	include "PolymorphicListIterator.hh"

#	include <iterator>

	namespace Entropy
	{
		template<typename T>
		PolymorphicListIterator<T>::PolymorphicListIterator(const typename std::list<std::shared_ptr<T>>::iterator &i)
			: _me(i)
		{}

		template<typename T> PolymorphicListIterator<T>::~PolymorphicListIterator() = default;

		template<typename T>
		T &PolymorphicListIterator<T>::operator * ()
		{
			return *_me->get();
		}

		template<typename T>
		T *PolymorphicListIterator<T>::operator -> ()
		{
			return _me->get();
		}

		template<typename T>
		std::shared_ptr<T> &PolymorphicListIterator<T>::shared()
		{
			return *_me;
		}

		template<typename T>
		PolymorphicListIterator<T>::operator std::shared_ptr<T> &()
		{
			return *_me;
		}

		template<typename T>
		PolymorphicListIterator<T> &PolymorphicListIterator<T>::operator ++ ()
		{
			++_me;

			return *this;
		}

		template<typename T>
		PolymorphicListIterator<T> &PolymorphicListIterator<T>::operator -- ()
		{
			--_me;

			return *this;
		}

		template<typename T>
		PolymorphicListIterator<T> PolymorphicListIterator<T>::operator ++ (int)
		{
			auto ret = _me;

			++(*this);

			return ret;
		}

		template<typename T>
		PolymorphicListIterator<T> PolymorphicListIterator<T>::operator -- (int)
		{
			auto ret = _me;

			--(*this);

			return ret;
		}

		template<typename T>
		bool PolymorphicListIterator<T>::operator == (const PolymorphicListIterator<T> &o) const
		{
			return _me == o._me;
		}

		template<typename T>
		bool PolymorphicListIterator<T>::operator != (const PolymorphicListIterator<T> &o) const
		{
			return _me != o._me;
		}

		template<typename T>
		PolymorphicListConstIterator<T>::PolymorphicListConstIterator(const typename std::list<std::shared_ptr<T>>::const_iterator &i)
			: _me(i)
		{}

		template<typename T> PolymorphicListConstIterator<T>::~PolymorphicListConstIterator() = default;

		template<typename T>
		const T &PolymorphicListConstIterator<T>::operator * ()
		{
			return *_me->get();
		}

		template<typename T>
		const T *PolymorphicListConstIterator<T>::operator -> ()
		{
			return _me->get();
		}

		template<typename T>
		PolymorphicListConstIterator<T> &PolymorphicListConstIterator<T>::operator ++ ()
		{
			++_me;

			return *this;
		}

		template<typename T>
		PolymorphicListConstIterator<T> &PolymorphicListConstIterator<T>::operator -- ()
		{
			--_me;

			return *this;
		}

		template<typename T>
		PolymorphicListConstIterator<T> PolymorphicListConstIterator<T>::operator ++ (int)
		{
			auto ret = _me;

			++(*this);

			return ret;
		}

		template<typename T>
		PolymorphicListConstIterator<T> PolymorphicListConstIterator<T>::operator -- (int)
		{
			auto ret = _me;

			--(*this);

			return ret;
		}

		template<typename T>
		bool PolymorphicListConstIterator<T>::operator == (const PolymorphicListConstIterator<T> &o) const
		{
			return _me == o._me;
		}

		template<typename T>
		bool PolymorphicListConstIterator<T>::operator != (const PolymorphicListConstIterator<T> &o) const
		{
			return _me != o._me;
		}
	}

#endif
