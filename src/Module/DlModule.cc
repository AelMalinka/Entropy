/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "DlModule.hh"

using namespace Entropy;
using namespace std;

void DlModule_close(void *p)
{
	if(p != nullptr)
		dlclose(p);
}

DlModule::DlModule()
	: _handle()
{}

DlModule::DlModule(const string &name)
	: _handle(open(name), DlModule_close)
{}

DlModule::~DlModule() = default;

void DlModule::Load(const string &name)
{
	_handle = shared_ptr<void>(open(name), DlModule_close);
}

void DlModule::Unload()
{
	_handle.reset();
}

void *DlModule::open(const string &name)
{
	void *ret= dlopen(name.c_str(), RTLD_NOW);

	if(ret == nullptr)
		ENTROPY_THROW(ModuleError("dlopen error") <<
			DlOpenError(dlerror())
		);

	return ret;
}
