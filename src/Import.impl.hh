/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU General Public License v3
*/

#if !defined ENTROPY_MODULE_IMPL
#	define ENTROPY_MODULE_IMPL

#	include "Import.hh"
#	include <dlfcn.h>
	
	namespace Entropy
	{
		namespace _internal
		{
			inline int noop(void *)
			{
				return 0;
			}
		}

		template<typename Module>
		Import<Module>::Import(const std::string &n)
			: _dl_handle(nullptr, &_internal::noop), _obj_handle()
		{
			using std::unique_ptr;

			void *t_dl_handle = dlopen(n.c_str(), RTLD_NOW);

			if (t_dl_handle == nullptr)
				ENTROPY_THROW(ModuleError("dlopen error") << 
					DlOpenError(dlerror())
				);

			_dl_handle = unique_ptr<void, int (*)(void *)>(t_dl_handle, &dlclose);

			Module *(*t_new_handle)();
			void (*t_del_handle)(void *);

			//2013-12-12 AMR NOTE: Source: https://groups.google.com/d/msg/comp.lang.c++.moderated/BRVEES2ypvE/ov2hUcVl2NMJ
			*(void **)(&t_new_handle) = dlsym(_dl_handle.get(), "entropy_new\0");
			*(void **)(&t_del_handle) = dlsym(_dl_handle.get(), "entropy_delete\0");

			if(t_new_handle == nullptr || t_del_handle == nullptr)
				ENTROPY_THROW(ModuleError("dlsym error") <<
					DlOpenError(dlerror())
				);

			_internal::module_deleter t_deleter(t_del_handle);

			_obj_handle = unique_ptr<Module, _internal::module_deleter>(
				(*t_new_handle)(),
				t_deleter
			);
		}

		template<typename Module> Import<Module>::Import(Import<Module> &&) = default;
		template<typename Module> Import<Module>::~Import() = default;
		template<typename Module> Import<Module> &Import<Module>::operator = (Import<Module> &&) = default;

		template<typename Module>
		Module &Import<Module>::operator * ()
		{
			return *_obj_handle;
		}

		template<typename Module>
		Module *Import<Module>::operator -> ()
		{
			return _obj_handle.get();
		}

		namespace _internal
		{
			template<typename T>
			void module_deleter::operator () (T *r)
			{
				(*_deleter)(r);
			}
		}
	}

#endif
