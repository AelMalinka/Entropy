/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Loop.hh"

using namespace std;
using namespace boost;
using namespace Entropy::Asio;

MainLoop::MainLoop()
	: _loop(nullptr)
{
	_loop = new _loop_t;
	_loop->count = 1;
}

MainLoop::MainLoop(const MainLoop &o)
	: _loop(o._loop)
{
	++_loop->count;
}

MainLoop::~MainLoop()
{
	if(--_loop->count == 0)
		delete _loop;
}

MainLoop &MainLoop::operator = (const MainLoop &) = default;

any &MainLoop::handle()
{
	return _loop->data;
}

const any &MainLoop::handle() const
{
	return _loop->data;
}
