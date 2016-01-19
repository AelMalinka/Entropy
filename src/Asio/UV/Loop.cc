/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Loop.hh"

using namespace std;
using namespace boost;
using namespace Entropy::Asio::UV;

Loop::Loop()
	: Asio::Loop(_uv_handle())
{
	// 2016-01-19 AMR NOTE: due to mechanics of Asio::Loop this needs to be initialized AFTER handed to the boost::any, TODO
	uv_loop_init(Handle());
	Handle()->data = this;
}

void Loop::operator () ()
{
	uv_run(Handle(), UV_RUN_DEFAULT);
}

uv_loop_t *Loop::Handle()
{
	return any_cast<_uv_handle &>(handle()).handle();
}

Loop::_uv_handle::_uv_handle()
	: _handle()
{}

Loop::_uv_handle::~_uv_handle()
{
	uv_stop(&_handle);
	uv_loop_close(&_handle);
}

uv_loop_t *Loop::_uv_handle::handle()
{
	return &_handle;
}
