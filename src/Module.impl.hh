/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_MODULE_IMPL
#	define ENTROPY_MODULE_IMPL

#	include "Module.hh"

	namespace Entropy
	{
		template<typename F>
		std::function<F> Module::get(const std::string &name)
		{
			return _module.get<F>(name);
		}
	}

#endif
