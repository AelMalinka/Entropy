/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_MODULE_DLLMODULE_INC
#	define ENTROPY_MODULE_DLLMODULE_INC

#	include "Exception.hh"
#	include <functional>
#	include <memory>

#	include <Windows.h>

	namespace Entropy
	{
		ENTROPY_ERROR_INFO(DllName, std::string);
		ENTROPY_ERROR_INFO(DllError, DWORD);

		class DllModule
		{
			public:
				DllModule();
				explicit DllModule(const std::string &);
				~DllModule();
				template<typename F> std::function<F> get(const std::string &);
				void Load(const std::string &);
				void Unload();
			protected:
				void open(const std::string &);
			private:
				HMODULE _handle;
		};
	}

#	include <unordered_map>

#	include "DllModule.impl.hh"

#endif
