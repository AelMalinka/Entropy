/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#if !defined ENTROPY_MODULE_INC
#	define ENTROPY_MODULE_INC

#	include "Exception.hh"
#	include <memory>

	namespace Entropy
	{
		ENTROPY_EXCEPTION_BASE(ModuleError, "Module Error");
		ENTROPY_ERROR_INFO(DlOpenError, std::string);
		ENTROPY_ERROR_INFO(ModuleHandle, void *);

		namespace _internal
		{
			struct module_deleter
			{
				module_deleter();
				module_deleter(void (*) (void *));
				template<typename T> void operator() (T *);
				private:
					void (*_deleter)(void *);
			};
		}

		//2013-12-13 AMR TODO: encapsulate dl* from dlfcn into a Module class
		template<typename Interface>
		class Import
		{
			public:
				Import(const std::string &);
				Import(const Import<Interface> &);
				Import(Import<Interface> &&);
				virtual ~Import();
				Import<Interface> &operator = (const Import<Interface> &);
				Import<Interface> &operator = (Import<Interface> &&);
				Interface &operator *();
				Interface *operator->();
			protected:
				std::shared_ptr<void> _load(const std::string &) const;
				template<typename F> F *_load_func(const std::string &) const;
				std::unique_ptr<Interface, _internal::module_deleter> _new() const;
			private:
				std::shared_ptr<void> _dl_handle;
				std::unique_ptr<Interface, _internal::module_deleter> _obj_handle;
		};
	}

#	include "Import.impl.hh"

#endif
