/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#include "PyModule.hh"

using namespace Entropy;
using namespace std;

PyModule::PyModule() = default;
PyModule::~PyModule() = default;

PyModule::PyModule(const string &name)
	: BaseModule(open(name), [](void *){})
{}

void *PyModule::open(const string &)
{
	return nullptr;
}
