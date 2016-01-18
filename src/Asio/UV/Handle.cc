/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Handle.hh"

using namespace Entropy::Asio::UV;

Handle::Handle(Asio::Loop &l, uv_handle_t *h)
	: _loop(dynamic_cast<UV::Loop &>(l)), _handle(h)
{}

Handle::~Handle()
{
	if(!uv_is_closing(handle()))
		uv_close(handle(), NULL);
}

bool Handle::isActive() const
{
	return uv_is_active(const_cast<uv_handle_t *>(handle()));
}

bool Handle::isClosing() const
{
	return uv_is_closing(const_cast<uv_handle_t *>(handle()));
}

Loop &Handle::Owner()
{
	return _loop;
}

const Loop &Handle::Owner() const
{
	return _loop;
}

uv_handle_t *Handle::handle()
{
	return _handle;
}

const uv_handle_t *Handle::handle() const
{
	return _handle;
}
