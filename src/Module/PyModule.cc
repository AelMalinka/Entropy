/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "PyModule.hh"

using namespace Entropy;
using namespace Entropy::Python;
using namespace std;

Interpreter PyModule::_python;

PyModule::PyModule(const string &name)
	: _module(name)
{}

PyModule::~PyModule() = default;
