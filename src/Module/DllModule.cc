/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "DllModule.hh"

using namespace Entropy;
using namespace std;

DllModule::DllModule()
	: _handle(nullptr)
{}

DllModule::DllModule(const string &name)
	: _handle(nullptr)
{
	Load(name);
}

DllModule::~DllModule()
{
	Unload();
}

void DllModule::Load(const string &name)
{
	Unload();

	open(name);
}

void DllModule::Unload()
{
	if(_handle != nullptr)
		FreeLibrary(_handle);
}

void DllModule::open(const string &name)
{
	_handle = LoadLibrary(name.c_str());

	if(!_handle)
		ENTROPY_THROW(ModuleError("Failed to Load DLL") <<
			DllName(name) <<
			DllError(GetLastError())
		);
}
