/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_MODULE_IMPL
#	define ENTROPY_MODULE_IMPL

#	include "Module.hh"

#	include "Module/DlModule.hh"
#	ifdef HAVE_PYTHON
#		include "Module/PyModule.hh"
#	endif

	namespace Entropy
	{
		template<typename F>
		std::function<F> Module::get(const std::string &name) const
		{
			using internal::ModuleType;
			using boost::any_cast;

			DlModule dl;
#	ifdef HAVE_PYTHON
			PyModule py;
#	endif

			switch(_type)
			{
				case ModuleType::Dl:
					dl = any_cast<DlModule>(_module);
					return dl.get<F>(name);
				break;
#	ifdef HAVE_PYTHON
				case ModuleType::Py:
					ENTROPY_THROW(ModuleError("Python is currently unsupported"));
					//py = any_cast<PyModule>(_module);
					//return py.get<F>(name);
				break;
#	endif
				default:
					ENTROPY_THROW(ModuleError("Invalid ModuleType"));
				break;
			}
		}
	}

#endif
