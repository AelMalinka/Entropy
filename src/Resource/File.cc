/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "File.hh"

using namespace Entropy::Resource;
using namespace std;

string File::_type = "File"s;

File::File(const string &name, const Reference &root)
	: Handle(root), _name(name), _data()
{}

char *File::data()
{
	return const_cast<char *>(_data.data());
}

const char *File::data() const
{
	return _data.data();
}

const string &File::type() const
{
	return _type;
}

const string &File::name() const
{
	return _name;
}

void File::parse(const string &data)
{
	_data = data;
}

void File::release()
{
	_data.clear();
}
