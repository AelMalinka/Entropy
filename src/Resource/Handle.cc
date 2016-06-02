/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Handle.hh"

#include <boost/filesystem.hpp>
#include <fstream>

using namespace Entropy::Resource;
using namespace std;
using namespace boost::filesystem;

Handle::Handle(const Reference &ref)
	: _root(ref), _loaded(false)
{}

void Handle::load()
{
	using std::ifstream;
	using boost::filesystem::path;

	string data;
	path p("res" + this->path());

	if(exists(p))
	{
		_loaded = true;

		string where = p.string();
		ifstream file(where);
		string line;
		while(getline(file, line))
			data += line + "\n";
	}
	else
		ENTROPY_THROW(Exception("Resource doesn't exist"));

	parse(data);
}

void Handle::free()
{
	release();
	_loaded = false;
}

bool Handle::loaded() const
{
	return _loaded;
}

string Handle::filename() const
{
	return name();
}

string Handle::path() const
{
	return _root->path() + "/" + filename();
}
