/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_MODULE_DLMODULE_INC
#	define ENTROPY_MODULE_DLMODULE_INC

#	include "Exception.hh"
#	include <functional>
#	include <memory>

	namespace Entropy
	{
		ENTROPY_ERROR_INFO(DlName, std::string);
		ENTROPY_ERROR_INFO(DlOpenError, std::string);

		class DlModule
		{
			public:
				DlModule();
				explicit DlModule(const std::string &);
				~DlModule();
				template<typename F> std::function<F> get(const std::string &);
				void Load(const std::string &);
				void Unload();
			protected:
				void open(const std::string &);
			private:
				std::shared_ptr<void> _handle;
		};
	}

#	include <unordered_map>

#	define ENTROPY_MODULE(CLASS) ::std::unordered_map<void *, shared_ptr<CLASS>> _objects;\
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
