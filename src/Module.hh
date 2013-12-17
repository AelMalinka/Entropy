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
		ENTROPY_EXCEPTION(DeleteError, "entropy_delete", ModuleError);
		ENTROPY_ERROR_INFO(DlOpenError, std::string);
		ENTROPY_ERROR_INFO(ModuleHandle, void *);
		ENTROPY_ERROR_INFO(ObjectAddress, void *);

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

#	define ENTROPY_MODULE(CLASS) unordered_map<void *, shared_ptr<CLASS>> _objects;\
		extern "C" { \
		CLASS *entropy_new() {\
			shared_ptr<CLASS> t(new CLASS);\
			_objects[t.get()] = t;\
			return _objects[t.get()].get();\
		}\
		void entropy_delete(void *p) {\
			auto i = _objects.find(p);\
			if(i == _objects.end()) \
				ENTROPY_THROW(::Entropy::DeleteError("failed to find object in objects array") << ::Entropy::ObjectAddress(p)); \
			_objects.erase(i);}}

#	include "Module.impl.hh"

#endif
