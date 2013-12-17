/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#if !defined ENTROPY_MODULE_IMPL
#	define ENTROPY_MODULE_IMPL

#	include "Module.hh"
#	include <dlfcn.h>

	namespace Entropy
	{
		template<typename F>
		F &Module::get(const std::string &name) const
		{
			using std::function;

			F *addr;

			//2013-12-12 AMR NOTE: Source: https://groups.google.com/d/msg/comp.lang.c++.moderated/BRVEES2ypvE/ov2hUcVl2NMJ
			*(void **)(&addr) = dlsym(_handle.get(), name.c_str());
			if(addr == nullptr)
				ENTROPY_THROW(ModuleError("dlsym error") <<
					DlOpenError(dlerror()) <<
					ModuleHandle(_handle.get())
				);

			return *addr;
		}
	}

#endif
