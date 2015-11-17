/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_MODULE_DLMODULE_INC
#	define ENTROPY_MODULE_DLMODULE_INC

#	include "BaseModule.hh"

	namespace Entropy
	{
		ENTROPY_ERROR_INFO(DlOpenError, std::string);

		class DlModule :
			public BaseModule
		{
			public:
				DlModule();
				explicit DlModule(const std::string &);
				virtual ~DlModule();
				template<typename F> F &get(const std::string &);
			protected:
				virtual void *open(const std::string &);
		};
	}

#	define ENTROPY_MODULE(CLASS) unordered_map<void *, shared_ptr<CLASS>> _objects;\
		extern "C" { \
		CLASS *entropy_new() {\
			::std::shared_ptr<CLASS> t = ::std::make_shared<CLASS>();\
			_objects[t.get()] = t;\
			return _objects[t.get()].get();\
		}\
		void entropy_delete(void *p) {\
			auto i = _objects.find(p);\
			if(i == _objects.end()) \
				ENTROPY_THROW(::Entropy::DeleteError("failed to find object in objects array") << ::Entropy::ObjectAddress(p)); \
			_objects.erase(i);}}

#	include "DlModule.impl.hh"

#endif
