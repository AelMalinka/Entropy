/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Module.hh"

using namespace Entropy::Python;
using namespace std;

Module::Module(const string &name)
	: Object()
{
	PyObject *handle = PyImport_ImportModule(name.c_str());

	if(handle == nullptr)
		ENTROPY_THROW(PythonError("Module not found") <<
			ModuleName(name)
		);

	Handle(handle);
}

Module::~Module() = default;
