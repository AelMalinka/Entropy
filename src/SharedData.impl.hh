/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_SHAREDDATA_IMPL
#	define ENTROPY_SHAREDDATA_IMPL

#	include "SharedData.hh"
#	include <utility>

	namespace Entropy
	{
		template<typename T>
		std::size_t SharedData<T>::_count(0);

		template<typename T>
		std::shared_ptr<T> SharedData<T>::_shared_data;

		template<typename T>
		template<typename ...Args>
		SharedData<T>::SharedData(Args && ...args)
		{
			if(_count++ == 0) {
				_shared_data = std::make_shared<T>(std::forward<Args>(args)...);
			}
		}

		template<typename T>
		SharedData<T>::SharedData(const SharedData<T> &)
		{
			++_count;
		}

		template<typename T>
		SharedData<T>::SharedData(SharedData<T> &&)
		{
			++_count;
		}

		template<typename T>
		SharedData<T>::~SharedData()
		{
			if(--_count == 0) {
				_shared_data.reset();
			}
		}

		template<typename T>
		std::shared_ptr<T> SharedData<T>::shared() const
		{
			return _shared_data;
		}
	}

#endif
