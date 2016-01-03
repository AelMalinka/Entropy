/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Loop.hh"

using namespace Entropy::Asio::UV;

Loop::Loop()
	: _loop(nullptr)
{
	_loop = new _loop_t;
	_loop->count = 1;
	uv_loop_init(Handle());
}

Loop::Loop(const Loop &o)
	: _loop(nullptr)
{
	_loop = o._loop;
	++_loop->count;
}

Loop::~Loop()
{
	if(--_loop->count == 0)
	{
		uv_stop(Handle());
		uv_loop_close(Handle());
		delete _loop;
	}
}

Loop &Loop::operator = (const Loop &) = default;

void Loop::operator () ()
{
	uv_run(Handle(), UV_RUN_DEFAULT);
}

uv_loop_t *Loop::Handle() const
{
	return &_loop->handle;
}
