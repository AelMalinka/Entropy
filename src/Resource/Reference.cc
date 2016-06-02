/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Reference.hh"
#include "Handle.hh"
#include "Folder.hh"

using namespace Entropy::Resource;
using namespace std;

map<Handle *, unsigned int> Reference::_refs;

Reference::Reference(Handle *handle)
	: _handle(handle)
{
	if(_handle != nullptr)
	{
		++_refs[_handle];

		if(!_handle->loaded())
			_handle->load();
	}
}

Reference::Reference(const Reference &o)
	: _handle(o._handle)
{
	if(_handle != nullptr)
	{
		++_refs[_handle];

		if(!_handle->loaded())
			_handle->load();
	}
}

Reference::Reference(Reference &&o)
	: _handle(o._handle)
{
	o._handle = nullptr;
}

Reference::~Reference()
{
	if(_handle != nullptr)
		if(--_refs[_handle] == 0)
			if(_handle->loaded())
				_handle->free();
}

Reference &Reference::operator = (const Reference &o)
{
	_handle = o._handle;

	if(_handle != nullptr)
	{
		++_refs[_handle];

		if(!_handle->loaded())
			_handle->load();
	}

	return *this;
}

Reference &Reference::operator = (Reference &&o)
{
	_handle = o._handle;
	o._handle = nullptr;

	return *this;
}

Handle *Reference::get()
{
	return _handle;
}

Handle &Reference::operator * ()
{
	if(_handle == nullptr)
		ENTROPY_THROW(Exception("Invalid Resource"));

	return *_handle;
}

Handle *Reference::operator -> ()
{
	if(_handle == nullptr)
		ENTROPY_THROW(Exception("Invalid Resource"));

	return _handle;
}

const Handle *Reference::get() const
{
	if(_handle == nullptr)
		ENTROPY_THROW(Exception("Invalid Resource"));

	return _handle;
}

const Handle &Reference::operator * () const
{
	if(_handle == nullptr)
		ENTROPY_THROW(Exception("Invalid Resource"));

	return *_handle;
}

const Handle *Reference::operator -> () const
{
	if(_handle == nullptr)
		ENTROPY_THROW(Exception("Invalid Resource"));

	return _handle;
}

Handle *Reference::operator [] (const string &name)
{
	if(_handle == nullptr)
		ENTROPY_THROW(Exception("Invalid Resource"));

	if(_handle->type() != "Folder")
		ENTROPY_THROW(Exception("Trying to index file resource"));

	return (*dynamic_cast<Folder *>(_handle))[name];
}
