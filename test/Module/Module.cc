/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU General Lesser Public License v3
*/

#include <memory>
#include <unordered_map>
#include <iostream>
#include "Module.hh"
#include "Exception.hh"

using namespace std;
using namespace ::tests;

Module::Module() = default;
Module::~Module() = default;

void Module::run()
{
	cout << "Module::run()" << endl;
}

const string &Module::operator [] (const string &val)
{
	cout << "Module::operator[]: " << val << endl;
	return val;
}

int Module::operator [] (const int val)
{
	cout << "Module::operator[]: " << val << endl;
	return val;
}

Interface &Module::operator = (const int val)
{
	cout << "Module::operator = " << val << endl;
	return *this;
}

unordered_map<void *, shared_ptr<Module>> _modules;
ENTROPY_ERROR_INFO(ModulePointer, void *); 
ENTROPY_EXCEPTION_BASE(DeleteError, "entropy_delete error");

Module *entropy_new() {
	shared_ptr<Module> t(new Module);
	_modules[t.get()] = t;
	return _modules[t.get()].get();
}

void entropy_delete(void *p) {
	using namespace Entropy;

	if(_modules.find(p) == _modules.end()) {
		ENTROPY_THROW(DeleteError("ptr and _module differ") <<
			ModulePointer(p)
		);
	}
	_modules.erase(p);
}
