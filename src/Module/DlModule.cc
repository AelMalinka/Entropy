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
	: _handle()
{
	Load(name);
}

DlModule::~DlModule() = default;

void DlModule::Load(const string &name)
{
	open(name);
}

void DlModule::Unload()
{
	_handle.reset();
}

void DlModule::open(const string &name)
{
	void *ret= dlopen(name.c_str(), RTLD_NOW);

	if(!ret) {
		auto s = dlerror();

		ENTROPY_THROW(ModuleError(s) <<
			DlName(name) <<
			DlOpenError(s)
		);
	}

	_handle = shared_ptr<void>(ret, DlModule_close);
}
