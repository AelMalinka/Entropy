/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "PyModule.hh"

using namespace Entropy;
using namespace Entropy::Python;
using namespace std;

Interpreter PyModule::_python;

PyModule::PyModule() = default;
PyModule::~PyModule() = default;

PyModule::PyModule(const string &name)
	: BaseModule(open(name), [](void *p){delete static_cast<Module *>(p);})
{}

void *PyModule::open(const string &name)
{
	auto p = new Module(name);
	if(p == nullptr)
		ENTROPY_THROW(PythonError("Module not instantiated"));
	return p;
}
