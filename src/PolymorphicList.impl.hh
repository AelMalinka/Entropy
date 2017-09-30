/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_POLYMORPHICLIST_IMPL
#	define ENTROPY_POLYMORPHICLIST_IMPL

#	include "PolymorphicList.hh"
#	include <utility>

	namespace Entropy
	{
		template<typename T> PolymorphicList<T>::PolymorphicList() = default;
		template<typename T> PolymorphicList<T>::PolymorphicList(const PolymorphicList<T> &) = default;
		template<typename T> PolymorphicList<T>::PolymorphicList(PolymorphicList<T> &&) = default;
		template<typename T> PolymorphicList<T>::~PolymorphicList() = default;

		template<typename T>
		void PolymorphicList<T>::clear()
		{
			_list.clear();
		}

		template<typename T>
		void PolymorphicList<T>::push_front(const std::shared_ptr<T> &v)
		{
			_list.push_front(v);
		}

		template<typename T>
		template<typename U, typename>
		void PolymorphicList<T>::push_front(U &&v)
		{
			_list.push_front(std::make_shared<U>(std::move(v)));
		}

		template<typename T>
		void PolymorphicList<T>::push_front(T *v)
		{
			_list.push_front(std::shared_ptr<T>(v));
		}

		template<typename T>
		template<typename U, typename ...Args>
		void PolymorphicList<T>::emplace_front(Args && ...args)
		{
			_list.push_front(std::make_shared<U>(std::forward<Args>(args)...));
		}

		template<typename T>
		void PolymorphicList<T>::push_back(const std::shared_ptr<T> &v)
		{
			_list.push_back(v);
		}

		template<typename T>
		template<typename U, typename>
		void PolymorphicList<T>::push_back(U &&v)
		{
			_list.push_back(std::make_shared<U>(std::move(v)));
		}

		template<typename T>
		void PolymorphicList<T>::push_back(T *v)
		{
			_list.push_back(std::shared_ptr<T>(v));
		}

		template<typename T>
		template<typename U, typename ...Args>
		void PolymorphicList<T>::emplace_back(Args && ...args)
		{
			_list.push_back(std::make_shared<U>(std::forward<Args>(args)...));
		}

		template<typename T>
		std::size_t PolymorphicList<T>::size() const
		{
			return _list.size();
		}

		template<typename T>
		typename PolymorphicList<T>::iterator PolymorphicList<T>::begin()
		{
			return _list.begin();
		}

		template<typename T>
		typename PolymorphicList<T>::iterator PolymorphicList<T>::end()
		{
			return _list.end();
		}

		template<typename T>
		typename PolymorphicList<T>::const_iterator PolymorphicList<T>::begin() const
		{
			return _list.begin();
		}

		template<typename T>
		typename PolymorphicList<T>::const_iterator PolymorphicList<T>::end() const
		{
			return _list.end();
		}

		template<typename T>
		T &PolymorphicList<T>::front()
		{
			return *_list.front();
		}

		template<typename T>
		T &PolymorphicList<T>::back()
		{
			return *_list.back();
		}

		template<typename T>
		const T &PolymorphicList<T>::front() const
		{
			return *_list.front();
		}

		template<typename T>
		const T &PolymorphicList<T>::back() const
		{
			return *_list.back();
		}

		template<typename T>
		T &PolymorphicList<T>::operator [] (const std::size_t &p)
		{
			return *_list[p];
		}

		template<typename T>
		const T &PolymorphicList<T>::operator [] (const std::size_t &p) const
		{
			return *_list[p];
		}
	}

#endif
