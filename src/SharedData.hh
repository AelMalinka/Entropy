/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_SHARED_DATA_INC
#	define ENTROPY_SHARED_DATA_INC

#	include <memory>

	namespace Entropy
	{
		template<typename T>
		class SharedData
		{
			public:
				template<typename ...Args>
				explicit SharedData(Args && ...);
				SharedData(const SharedData<T> &);
				SharedData(SharedData<T> &&);
				virtual ~SharedData();
				SharedData<T> &operator = (const SharedData<T> &);
				SharedData<T> &operator = (SharedData<T> &&);
			protected:
				std::shared_ptr<T> shared() const;
			private:
				static std::size_t _count;
				static std::shared_ptr<T> _shared_data;
		};
	}

#	include "SharedData.impl.hh"

#endif
