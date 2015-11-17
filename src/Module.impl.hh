/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#if !defined ENTROPY_MODULE_IMPL
#	define ENTROPY_MODULE_IMPL

#	include "Module.hh"

#	include "Module/DlModule.hh"
#	include "Module/PyModule.hh"

	namespace Entropy
	{
		template<typename F> F &Module::get(const std::string &name) const
		{
			using internal::ModuleType;
			using boost::any_cast;

			F *f = nullptr;

			DlModule dl;
			PyModule py;

			switch(_type)
			{
				case ModuleType::Dl:
					dl = any_cast<DlModule>(_module);
					f = dl.get<F>(name);
				break;
				case ModuleType::Py:
					py = any_cast<PyModule>(_module);
					f = py.get<F>(name);
				break;
				default:
				break;
			}

			if(f == nullptr)
				ENTROPY_THROW(ModuleError("Invalid ModuleType"));

			return *f;
		}
	}

#endif
