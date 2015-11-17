/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_MODULE_INC
#	define ENTROPY_MODULE_INC

#	include "Exception.hh"
#	include <memory>
#	include <boost/any.hpp>

	namespace Entropy
	{
		namespace internal
		{
			enum class ModuleType
			{
				Dl,
				Py,
				Pl
			};
		}

		class Module
		{
			public:
				explicit Module(const std::string &);
				template<typename F> F &get(const std::string &) const;
			private:
				internal::ModuleType _type;
				boost::any _module;
		};
	}

#	include "Module.impl.hh"

#endif
