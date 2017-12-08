/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "DllModule.hh"

using namespace Entropy;
using namespace std;

void DllModule_close(void *p)
{
	if(p != nullptr)
		FreeLibrary(p);
}

DllModule::DllModule()
	: _handle()
{}

DllModule::DllModule(const string &name)
	: _handle()
{
	Load(name);
}

DllModule::~DllModule()
{
	Unload();
}

void DllModule::Load(const string &name)
{
	open(name);
}

void DllModule::Unload()
{
	_handle.reset();
}

void DllModule::open(const string &name)
{
	void *ret = LoadLibrary(name.c_str());

	if(!_handle) {
		auto s = GetLastError();

		ENTROPY_THROW(ModuleError(s) <<
			DllName(name) <<
			DllError(s)
		);
	}

	_handle = shared_ptr<void>(ret, DllModule_close);
}
