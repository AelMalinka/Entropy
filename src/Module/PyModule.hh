/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_MODULE_PYMODULE_INC
#	define ENTROPY_MODULE_PYMODULE_INC

#	include "Exception.hh"
#	include "SharedData.hh"
#	include "../Python/Interpreter.hh"
#	include "../Python/Module.hh"
#	include <functional>

	namespace Entropy
	{
		class PyModule :
			private SharedData<Python::Interpreter>
		{
			public:
				explicit PyModule(const std::string &);
				virtual ~PyModule();
				template<typename F> std::function<F> get(const std::string &) const;
			private:
				Python::Module _module;
		};
	}

#	include "PyModule.impl.hh"

#endif
