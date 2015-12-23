/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_MODULE_INC
#	define ENTROPY_MODULE_INC

#	ifdef HAVE_CONFIG_H
#		include "config.h"
#	endif

#	ifdef HAVE_PYTHON
#		include <Python.h>
#	endif

#	include "Exception.hh"
#	include <memory>
#	include <boost/any.hpp>
#	include <functional>

	namespace Entropy
	{
		namespace detail
		{
			enum class ModuleType
			{
				Dl,
				Py,
				Pl
			};
		}

		ENTROPY_ERROR_INFO(ModuleTypeStr, std::string);
		class Module
		{
			public:
				explicit Module(const std::string &);
				template<typename F> std::function<F> get(const std::string &) const;
			private:
				detail::ModuleType _type;
				boost::any _module;
		};
	}

#	include "Module.impl.hh"

#endif
