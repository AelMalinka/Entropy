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

		class Module
		{
			public:
				Module(const std::string &);
				Module(const Module &);
				Module(Module &&);
				virtual ~Module();
				template<typename F> F &get(const std::string &) const;
				Module &operator = (const Module &);
				Module &operator = (Module &&);
			protected:
			private:
				std::shared_ptr<void> _handle;
		};
	}

#	include "Module.impl.hh"

#endif
