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

		template<typename Module>
		class Import
		{
			public:
				//2013-12-12 AMR TODO: copy-constructor (copy a new object using previous func handles)
				Import(const std::string &);
				Import(Import<Module> &&);
				virtual ~Import();
				Import<Module> &operator = (Import<Module> &&);
				Module &operator *();
				Module *operator->();
			private:
				std::unique_ptr<void, int (*)(void *)> _dl_handle;
				std::unique_ptr<Module, _internal::module_deleter> _obj_handle;
		};
	}

#	include "Import.impl.hh"

#endif
