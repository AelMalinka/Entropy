/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Folder.hh"
#include "../Resource.hh"

#include <boost/filesystem.hpp>

using namespace Entropy::Resource;
using namespace std;
using namespace boost::filesystem;

string Folder::_type = "Folder"s;

Folder::Folder(const string &name, const Reference &root)
	: Handle(root), _name(name), _contents(), _loaded(false)
{}

void Folder::load()
{
	using boost::filesystem::path;

	_loaded = true;

	path p("res" + this->path());
	for(auto &&d : directory_iterator(p))
	{
		Handle *ret = detail::state.make(d.path().filename().string(), this);
		string where = d.path().filename().string();
		_contents[where] = ret;
	}
}

void Folder::free()
{
	_contents.clear();

	_loaded = false;
}

bool Folder::loaded() const
{
	return _loaded;
}

char *Folder::data()
{
	return nullptr;
}

const char *Folder::data() const
{
	return nullptr;
}

const string &Folder::type() const
{
	return _type;
}

const string &Folder::name() const
{
	return _name;
}

Handle *Folder::operator [] (const string &name)
{
	try
	{
		return _contents.at(name);
	}
	catch(exception &e)
	{
		ENTROPY_THROW(Exception("Not Found")
			<< LowerException(e)
		);
	}
}

void Folder::parse(const string &)
{}

void Folder::release()
{}
