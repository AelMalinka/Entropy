/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Interpreter.hh"

using namespace Entropy::Python;
using namespace std;

size_t Interpreter::_count = 0;

Interpreter::Interpreter()
{
	if(_count++ == 0)
		Py_Initialize();
}

Interpreter::~Interpreter()
{
	if(--_count == 0)
		Py_Finalize();
}
