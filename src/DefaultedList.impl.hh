/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_DEFAULTED_LIST_IMPL
#	define ENTROPY_DEFAULTED_LIST_IMPL

#	include "DefaultedList.hh"

	namespace Entropy
	{
		template<typename T>
		template<typename ...Args>
		DefaultedList<T>::DefaultedList(Args && ...args)
			: _list(), _default(_list.end())
		{
			_list.emplace_back(std::forward<Args>(args)...);
			_default = _list.begin();
		}

		template<typename T>
		DefaultedList<T>::DefaultedList(const T &v)
			: _list(), _default(_list.end())
		{
			_list.push_back(v);
			_default = _list.begin();
		}

		template<typename T>
		DefaultedList<T>::DefaultedList(T &&v)
			: _list(), _default(_list.end())
		{
			_list.push_back(std::move(v));
			_default = _list.begin();
		}

		template<typename T>
		DefaultedList<T>::DefaultedList(std::initializer_list<T> il)
			: _list(il), _default(_list.begin())
		{}

		template<typename T> DefaultedList<T>::DefaultedList(const DefaultedList<T> &) = default;
		template<typename T> DefaultedList<T>::DefaultedList(DefaultedList<T> &&) = default;
		template<typename T> DefaultedList<T>::~DefaultedList() = default;

		template<typename T>
		typename DefaultedList<T>::iterator DefaultedList<T>::current()
		{
			return _default;
		}

		template<typename T>
		typename DefaultedList<T>::const_iterator DefaultedList<T>::current() const
		{
			return _default;
		}

		template<typename T>
		T &DefaultedList<T>::get()
		{
			return *_default;
		}

		template<typename T>
		T &DefaultedList<T>::operator * ()
		{
			return *_default;
		}

		template<typename T>
		T *DefaultedList<T>::operator -> ()
		{
			return &*_default;
		}

		template<typename T>
		const T &DefaultedList<T>::get() const
		{
			return *_default;
		}

		template<typename T>
		const T &DefaultedList<T>::operator * () const
		{
			return *_default;
		}

		template<typename T>
		const T *DefaultedList<T>::operator -> () const
		{
			return &*_default;
		}

		template<typename T>
		void DefaultedList<T>::setDefault(const iterator &i)
		{
			_default = i;
		}

		template<typename T>
		void DefaultedList<T>::setDefault(const const_iterator &i)
		{
			_default = _list.begin();
			std::advance(_default, std::distance<const_iterator>(_default, i));
		}

		template<typename T>
		T &DefaultedList<T>::front()
		{
			return _list.front();
		}

		template<typename T>
		T &DefaultedList<T>::back()
		{
			return _list.back();
		}

		template<typename T>
		typename DefaultedList<T>::iterator DefaultedList<T>::begin()
		{
			return _list.begin();
		}

		template<typename T>
		typename DefaultedList<T>::iterator DefaultedList<T>::end()
		{
			return _list.end();
		}

		template<typename T>
		T &DefaultedList<T>::operator [] (const std::size_t &pos)
		{
			return _list[pos];
		}

		template<typename T>
		const T &DefaultedList<T>::front() const
		{
			return _list.front();
		}

		template<typename T>
		const T &DefaultedList<T>::back() const
		{
			return _list.back();
		}

		template<typename T>
		typename DefaultedList<T>::const_iterator DefaultedList<T>::begin() const
		{
			return _list.cbegin();
		}

		template<typename T>
		typename DefaultedList<T>::const_iterator DefaultedList<T>::end() const
		{
			return _list.cend();
		}

		template<typename T>
		const T &DefaultedList<T>::operator [] (const std::size_t &pos) const
		{
			return _list[pos];
		}

		template<typename T>
		std::size_t DefaultedList<T>::size() const
		{
			return _list.size();
		}

		template<typename T>
		void DefaultedList<T>::push_front(const T &v)
		{
			_list.push_front(v);
		}

		template<typename T>
		void DefaultedList<T>::push_front(T &&v)
		{
			_list.push_front(std::move(v));
		}

		template<typename T>
		template<typename ...Args>
		void DefaultedList<T>::emplace_front(Args && ...args)
		{
			_list.emplace_front(std::forward<Args>(args)...);
		}

		template<typename T>
		void DefaultedList<T>::push_back(const T &v)
		{
			_list.push_back(v);
		}

		template<typename T>
		void DefaultedList<T>::push_back(T &&v)
		{
			_list.push_back(std::move(v));
		}

		template<typename T>
		template<typename ...Args>
		void DefaultedList<T>::emplace_back(Args && ...args)
		{
			_list.emplace_back(std::forward<Args>(args)...);
		}

		template<typename T>
		template<typename ...Args>
		void DefaultedList<T>::clear(Args && ...args)
		{
			_list.clear();

			_list.emplace_back(std::forward<Args>(args)...);
			_default = _list.begin();
		}

		template<typename T>
		void DefaultedList<T>::erase(const typename DefaultedList<T>::iterator &i)
		{
			if(i == _default)
				ENTROPY_THROW(DefaultedListException("Trying to erase default"));

			_list.erase(i);
		}
	}

#endif
