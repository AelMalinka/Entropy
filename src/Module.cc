/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#include "Module.hh"

using namespace Entropy;
using namespace std;

Module::Module(const string &name)
{
	using internal::ModuleType;

	auto type = ""s;
	if(name.find(".") != string::npos)
		type = name.substr(name.find("."), name.size() - name.find("."));

	if(type == ".so")
	{
		_type = ModuleType::Dl;
		_module = DlModule(name);
	}
	else if(type == ".py")
	{
		_type = ModuleType::Py;
		_module = PyModule(name);
	}
	else
		ENTROPY_THROW(ModuleError("Failed to determine module") <<
			ModuleName(name)
		);
}
