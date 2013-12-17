/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#include "Module.hh"

#include <dlfcn.h>

using namespace Entropy;
using namespace std;

Module::Module(const string &name)
	: _handle(nullptr)
{
	_handle = shared_ptr<void>(dlopen(name.c_str(), RTLD_NOW), &dlclose);

	if(_handle == nullptr)
		ENTROPY_THROW(ModuleError("dlopen error") <<
			DlOpenError(dlerror())
		);
}

Module::Module(const Module &) = default;
Module::Module(Module &&) = default;
Module::~Module() = default;

Module &Module::operator = (const Module &) = default;
Module &Module::operator = (Module &&) = default;
