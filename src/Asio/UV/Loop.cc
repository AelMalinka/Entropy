/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Loop.hh"
#include <utility>

using namespace std;
using namespace boost;
using namespace Entropy::Asio::UV;

MainLoop::MainLoop()
	: Asio::MainLoop()
{
	handle() = _uv_handle();
	uv_loop_init(Handle());
	Handle()->data = this;
}

void MainLoop::operator () ()
{
	uv_run(Handle(), UV_RUN_DEFAULT);
}

uv_loop_t *MainLoop::Handle()
{
	return any_cast<_uv_handle &>(handle()).handle();
}

MainLoop::_uv_handle::_uv_handle()
	: _handle()
{}

MainLoop::_uv_handle::~_uv_handle()
{
	uv_stop(&_handle);
	uv_loop_close(&_handle);
}

uv_loop_t *MainLoop::_uv_handle::handle()
{
	return &_handle;
}
