/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_SHAREDDATA_IMPL
#	define ENTROPY_SHAREDDATA_IMPL

#	include "SharedData.hh"

	namespace Entropy
	{
		template<typename T>
		std::size_t SharedData<T>::_count(0);

		template<typename T>
		std::shared_ptr<T> SharedData<T>::_shared_data;

		template<typename T>
		SharedData<T>::SharedData()
		{
			if(_count++ == 0) {
				_shared_data = std::make_shared<T>();
			}
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
