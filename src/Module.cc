/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Module.hh"

using namespace Entropy;
using namespace std;

Module::Module()
	: _module()
{}

Module::Module(const string &name)
	: _module(name)
{}
