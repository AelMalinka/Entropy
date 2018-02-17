/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "PyModule.hh"

using namespace Entropy;
using namespace Entropy::Python;
using namespace std;

PyModule::PyModule(const string &name)
	: SharedData<Interpreter>(), _module(name)
{}

PyModule::~PyModule() = default;
