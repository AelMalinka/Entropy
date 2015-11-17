/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_MODULE_PYMODULE_IMPL
#	define ENTROPY_MODULE_PYMODULE_IMPL

#	include "PyModule.hh"

	namespace Entropy
	{
		template<typename F> F &PyModule::get(const std::string &) const
		{
			ENTROPY_THROW(ModuleError("Not implemented yet"));
		}
	}

#endif
