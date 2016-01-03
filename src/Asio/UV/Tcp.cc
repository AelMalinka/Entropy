/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Tcp.hh"

using namespace Entropy;
using namespace Entropy::Asio::UV;
using namespace std;


Tcp::Tcp(Loop &loop, const function<void(Stream &)> &con_cb, const function<void(Stream &, const string &)> &r_cb, const function<void(const Net::Exception &)> &error_cb)
	: Stream(loop, reinterpret_cast<uv_stream_t *>(&_handle), r_cb, error_cb), _handle(), _connect_cb(con_cb)
{
	_handle.data = this;

	int ret = uv_tcp_init(loop.Handle(), &_handle);
	if(ret != 0)
		ENTROPY_THROW(
			GeneralFailure("Failed to initialize libuv tcp object handle") <<
			SystemErrorCode(error_code(-ret, system_category())) <<
			SystemError(uv_strerror(ret))
		);
}

Tcp::~Tcp()
{}

void Tcp::ConnectCallback(Stream &sock)
{
	_connect_cb(sock);
	read_start();
}

void Tcp::connect(const struct sockaddr *addr)
{
	uv_connect_t *req = new uv_connect_t;
	req->data = this;

	int ret = uv_tcp_connect(req, &_handle, addr, _entropy_asio_uv_tcp_connect_cb);
	if(ret != 0)
		ENTROPY_THROW(
			GeneralFailure("Failed to connect to tcp socket") <<
			SystemErrorCode(error_code(-ret, system_category())) <<
			SystemError(uv_strerror(ret))
		);
}

int Tcp::sock_type()
{
	return SOCK_STREAM;
}

extern "C" {
	void _entropy_asio_uv_tcp_connect_cb(uv_connect_t *req, int status)
	{
		Tcp *tcp = reinterpret_cast<Tcp *>(req->data);
		delete req;

		if(status != 0)
			tcp->ErrorCallback(
				ENTROPY_ATTACH_TRACE(
					Net::Exception("Connection Error") <<
					SystemErrorCode(error_code(-status, system_category())) <<
					SystemError(uv_strerror(status))
				)
			);
		else
			tcp->ConnectCallback(*tcp);
	}
}
