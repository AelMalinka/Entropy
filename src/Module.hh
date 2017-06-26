/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_MODULE_INC
#	define ENTROPY_MODULE_INC

#	include "Module/DlModule.hh"

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
				DlModule _module;
		};
	}

#	include "Module.impl.hh"

#endif
