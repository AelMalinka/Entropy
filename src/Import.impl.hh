/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU General Public License v3
*/

#if !defined ENTROPY_MODULE_IMPL
#	define ENTROPY_MODULE_IMPL

#	include "Import.hh"
#	include <dlfcn.h>
	
	namespace Entropy
	{
		template<typename Interface>
		Import<Interface>::Import(const std::string &n)
			: _dl_handle(), _obj_handle()
		{
			_dl_handle = _load(n);
			_obj_handle = _new();
		}

		template<typename Interface>
		Import<Interface>::Import(const Import<Interface> &o)
			: _dl_handle(o._dl_handle), _obj_handle()
		{
			_obj_handle = _new();
		}

		template<typename Interface>
		std::shared_ptr<void> Import<Interface>::_load(const std::string &name) const
		{
			using std::move;
			using std::shared_ptr;

			void *t_dl_handle = dlopen(name.c_str(), RTLD_NOW);

			if (t_dl_handle == nullptr)
				ENTROPY_THROW(ModuleError("dlopen error") << 
					DlOpenError(dlerror())
				);

			shared_ptr<void> ret(t_dl_handle, dlclose);
			return move(ret);
		}

		template<typename Interface>
		std::unique_ptr<Interface, _internal::module_deleter> Import<Interface>::_new() const
		{
			using std::move;
			using std::unique_ptr;

			Interface *(*t_new_handle)() = _load_func<Interface *()>("entropy_new");
			void (*t_del_handle)(void *) = _load_func<void (void *)>("entropy_delete");

			_internal::module_deleter t_deleter(t_del_handle);
			Interface *t_ptr = (*t_new_handle)();

			unique_ptr<Interface, _internal::module_deleter> ret(t_ptr, t_deleter);
			return move(ret);
		}

		template<typename Interface>
		template<typename F>
		F *Import<Interface>::_load_func(const std::string &name) const
		{
			F *ret;

			//2013-12-12 AMR NOTE: Source: https://groups.google.com/d/msg/comp.lang.c++.moderated/BRVEES2ypvE/ov2hUcVl2NMJ
			*(void **)(&ret) = dlsym(_dl_handle.get(), name.c_str());

			if(ret == nullptr)
				ENTROPY_THROW(ModuleError("dlsym error") <<
					DlOpenError(dlerror()) <<
					ModuleHandle(_dl_handle.get())
				);

			return ret;
		}

		template<typename Interface> Import<Interface>::Import(Import<Interface> &&) = default;
		template<typename Interface> Import<Interface>::~Import() = default;
		template<typename Interface> Import<Interface> &Import<Interface>::operator = (const Import<Interface> &) = default;
		template<typename Interface> Import<Interface> &Import<Interface>::operator = (Import<Interface> &&) = default;

		template<typename Interface>
		Interface &Import<Interface>::operator * ()
		{
			return *_obj_handle;
		}

		template<typename Interface>
		Interface *Import<Interface>::operator -> ()
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
