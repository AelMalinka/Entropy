/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Root.hh"

using namespace Entropy::Resource;
using namespace std;

Root::Root()
	: Folder(_name, nullptr)
{}

void Root::free()
{}

string Root::filename() const
{
	return "/"s;
}

string Root::path() const
{
	return "";
}
