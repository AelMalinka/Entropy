/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_MODULE_INC
#	define ENTROPY_MODULE_INC

#	ifdef _POSIX_VERSION
#		include "Module/DlModule.hh"
#	elif defined _WIN32
#		include "Module/DllModule.hh"
#	endif

	namespace Entropy
	{
		ENTROPY_ERROR_INFO(ModuleTypeStr, std::string);
		class Module
		{
			public:
				Module();
				explicit Module(const std::string &);
				template<typename F> std::function<F> get(const std::string &);
				void Load(const std::string &);
				void Unload();
			private:
#				ifdef _POSIX_VERSION
					DlModule _module;
#				elif defined _WIN32
					DllModule _module;
#				endif
		};
	}

#	include "Module.impl.hh"

#endif
