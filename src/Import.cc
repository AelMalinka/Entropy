/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#include "Import.hh"

using namespace Entropy::_internal;

module_deleter::module_deleter() = default;

module_deleter::module_deleter(void (*deleter) (void *))
	: _deleter(deleter)
{}
