/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Module.hh"

using namespace Entropy;
using namespace std;

Module::Module(const string &name)
{
	using detail::ModuleType;

	auto type = ""s;
	if(name.rfind(".") != string::npos)
		type = name.substr(name.rfind("."), name.size() - name.rfind("."));

	if(type == ".so"s)
	{
		_type = ModuleType::Dl;
		_module = DlModule(name);
	}
#ifdef HAVE_PYTHON
	else if(type == ".py"s)
	{
		_type = ModuleType::Py;
		_module = PyModule(name.substr(0, name.size() - type.size()));
	}
#endif
	else
		ENTROPY_THROW(ModuleError("Failed to determine module type") <<
			ModuleName(name) <<
			ModuleTypeStr(type)
		);
}
