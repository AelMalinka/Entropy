/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Tcp.hh"

using namespace Entropy;
using namespace Entropy::Asio::UV;
using namespace std;


Tcp::Tcp(Asio::Loop &loop, const function<void(Stream &)> &con_cb, const function<void(Stream &)> &disc_cb, const function<void(Stream &, const string &)> &r_cb, const function<void(const Net::Exception &)> &error_cb)
	: Stream(loop, reinterpret_cast<uv_stream_t *>(&_handle), r_cb, error_cb), _handle(), _connect_cb(con_cb), _disconnect_cb(disc_cb)
{
	_handle.data = this;

	int ret = uv_tcp_init(dynamic_cast<UV::Loop &>(loop).Handle(), &_handle);
	if(ret != 0)
		ENTROPY_THROW(
			GeneralFailure("Failed to initialize libuv tcp object handle") <<
			SystemErrorCode(error_code(-ret, system_category())) <<
			SystemError(uv_strerror(ret))
		);
}

Tcp::~Tcp()
{}

const struct sockaddr Tcp::Socket() const
{
	struct sockaddr sock;
	int size = sizeof(sock);
	int ret = uv_tcp_getpeername(&_handle, &sock, &size);
	if(ret != 0)
		ENTROPY_THROW(
			GeneralFailure("Failed to get Socket") <<
			SystemErrorCode(error_code(-ret, system_category())) <<
			SystemError(uv_strerror(ret))
		);
	return sock;
}

void Tcp::ConnectCallback()
{
	read_start();
	_connect_cb(*this);
}

void Tcp::DisconnectCallback()
{
	read_stop();
	_disconnect_cb(*this);
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

void Tcp::bind(const struct sockaddr *addr)
{
	int ret = uv_tcp_bind(&_handle, addr, 0);
	if(ret != 0)
		ENTROPY_THROW(
			GeneralFailure("Failed to bind to port") <<
			SystemErrorCode(error_code(-ret, system_category())) <<
			SystemError(uv_strerror(ret))
		);
}

shared_ptr<Stream> Tcp::accept()
{
	return make_shared<Tcp>(
		Owner(),
		_connect_cb,
		_disconnect_cb,
		ReadCb(),
		ErrorCb()
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
			tcp->ConnectCallback();
	}
}
