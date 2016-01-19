/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Loop.hh"

using namespace std;
using namespace boost;
using namespace Entropy::Asio;

Loop::Loop(const any &v)
	: _loop(nullptr)
{
	_loop = new _loop_t;
	_loop->count = 1;

	_loop->data = v;
}

Loop::Loop(const Loop &o)
	: _loop(o._loop)
{
	++_loop->count;
}

Loop::~Loop()
{
	if(--_loop->count == 0)
		delete _loop;
}

Loop &Loop::operator = (const Loop &) = default;

any &Loop::handle()
{
	return _loop->data;
}

const any &Loop::handle() const
{
	return _loop->data;
}
