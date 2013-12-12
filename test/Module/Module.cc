/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU General Lesser Public License v3
*/

#include <memory>
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

unique_ptr<Module> _module;
ENTROPY_ERROR_INFO(ModulePointer, void *); 
ENTROPY_EXCEPTION_BASE(DeleteError, "entropy_delete error");

Module *entropy_new() {
	_module = unique_ptr<Module>(new Module);
	return _module.get();
}

void entropy_delete(void *p) {
	using namespace Entropy;

	if(p != _module.get()) {
		ENTROPY_THROW(DeleteError("ptr and _module differ") <<
			ModulePointer(p) <<
			ModulePointer(_module.get())
		);
	}
	_module.reset();
}
