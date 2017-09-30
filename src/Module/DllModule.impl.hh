/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_MODULE_DLLMODULE_IMPL
#	define ENTROPY_MODULE_DLLMODULE_IMPL

#	include "DllModule.hh"

	namespace Entropy
	{
		namespace detail
		{
			template<typename T>
			struct FuncType {};

			template<typename R, typename ...A>
			struct FuncType<R(A...)>
			{
				static std::function<R(A...)> create(const FARPROC addr)
				{
					return std::function<R(A...)>(reinterpret_cast<R(__stdcall *)(A...)>(addr));
				}
			};
		}

		template<typename F>
		std::function<F> DllModule::get(const std::string &name)
		{
			FARPROC addr = GetProcAddress(_handle, name.c_str());

			if(!addr)
				ENTROPY_THROW(ModuleError("GetProcAddress error") <<
					DllError(GetLastError()) <<
					ModuleHandle(_handle)
				);

			return detail::FuncType<T>::create(addr);
		}
	}

#endif
