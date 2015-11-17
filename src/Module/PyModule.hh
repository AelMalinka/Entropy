/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#if !defined ENTROPY_MODULE_PYMODULE_INC
#	define ENTROPY_MODULE_PYMODULE_INC

#	include "BaseModule.hh"

	namespace Entropy
	{
		class PyModule :
			public BaseModule
		{
			public:
				PyModule();
				PyModule(const std::string &);
				virtual ~PyModule();
				template<typename F> F &get(const std::string &) const;
			protected:
				virtual void *open(const std::string &);
		};
	}

#	include "PyModule.impl.hh"

#endif
