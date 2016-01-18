/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Stream.hh"
#include <cstring>

using namespace Entropy;
using namespace Entropy::Asio::UV;
using namespace std;

struct write_cb_data {
	Stream *stream;
	uv_buf_t *buff;
};

struct info_cb_data {
	Stream *stream;
	struct addrinfo *hints;
};

Stream::Stream(Asio::Loop &loop, uv_stream_t *handle, const function<void(Stream &, const string &)> &cb, const function<void(const Net::Exception &)> &err)
	: Handle(loop, reinterpret_cast<uv_handle_t *>(handle)), _handle(handle), _lookup(nullptr), _clients(), _read_cb(cb), _error_cb(err)
{}

Stream::~Stream()
{
	delete _lookup;
}

void Stream::Connect(const string &h, const string &s)
{
	if(_lookup != nullptr)
		delete _lookup;

	_lookup = new GetAddrInfo(Owner(), std::bind(&Stream::ConnectInfoCallback, ref(*this), placeholders::_1), h, s, sock_type());
}

void Stream::Listen(const string &h, const string &s)
{
	if(_lookup != nullptr)
		delete _lookup;

	_lookup = new GetAddrInfo(Owner(), std::bind(&Stream::ListenInfoCallback, ref(*this), placeholders::_1), h, s, sock_type());
}

void Stream::Disconnect()
{
	read_stop();

	if(!uv_is_closing(handle()))
		uv_close(handle(), NULL);
}

void Stream::Write(const string &s)
{
	uv_write_t *req = new uv_write_t;
	write_cb_data *data = new write_cb_data;
	req->data = data;

	data->stream = this;
	data->buff = new uv_buf_t;
	data->buff->len = s.size();
	
	data->buff->base = new char[s.size()];
	memcpy(data->buff->base, s.data(), s.size());

	int ret = uv_write(req, stream(), data->buff, 1, _entropy_asio_uv_stream_write_cb);
	if(ret < 0)
		ENTROPY_THROW(
			GeneralFailure("failed to write to socket") <<
			SystemErrorCode(error_code(-ret, system_category())) <<
			SystemError(uv_strerror(ret))
		);
}

bool Stream::isReadable() const
{
	return uv_is_readable(stream());
}

bool Stream::isWritable() const
{
	return uv_is_writable(stream());
}

uv_stream_t *Stream::stream()
{
	return _handle;
}

const uv_stream_t *Stream::stream() const
{
	return _handle;
}

void Stream::read_start()
{
	int ret = uv_read_start(stream(), _entropy_asio_uv_stream_alloc_cb, _entropy_asio_uv_stream_read_cb);
	if(ret < 0)
		ENTROPY_THROW(
			GeneralFailure("Read failed") <<
			SystemErrorCode(error_code(-ret, system_category())) <<
			SystemError(uv_strerror(ret))
		);
}

void Stream::read_stop()
{
	int ret = uv_read_stop(stream());
	if(ret < 0)
		ENTROPY_THROW(
			GeneralFailure("Stopping read failed") <<
			SystemErrorCode(error_code(-ret, system_category())) <<
			SystemError(uv_strerror(ret))
		);
}

function<void(Stream &, const string &)> &Stream::ReadCb()
{
	return _read_cb;
}

function<void(const Net::Exception &)> &Stream::ErrorCb()
{
	return _error_cb;
}

const function<void(Stream &, const string &)> &Stream::ReadCb() const
{
	return _read_cb;
}

const function<void(const Net::Exception &)> &Stream::ErrorCb() const
{
	return _error_cb;
}

void Stream::ReadCallback(const string &data)
{
	_read_cb(*this, data);
}

void Stream::ErrorCallback(const Net::Exception &err)
{
	_error_cb(err);
}

void Stream::ListenInfoCallback(struct addrinfo *res)
{
	bind(res->ai_addr);
	int ret = uv_listen(stream(), 128, _entropy_asio_uv_stream_accept_cb);
	if(ret < 0)
		ENTROPY_THROW(
			GeneralFailure("Listen failed") <<
			SystemErrorCode(error_code(-ret, system_category())) <<
			SystemError(uv_strerror(ret))
		);
}

void Stream::ConnectInfoCallback(struct addrinfo *res)
{
	connect(res->ai_addr);
}

void Stream::AcceptCallback()
{
	shared_ptr<Stream> sock = accept();
	_clients.push_back(sock);
	uv_accept(stream(), sock->stream());
	sock->ConnectCallback();
}

extern "C" {
	void _entropy_asio_uv_stream_alloc_cb(uv_handle_t *, size_t size, uv_buf_t *buffer)
	{
		buffer->base = new char[size];
		buffer->len = size;
	}

	void _entropy_asio_uv_stream_read_cb(uv_stream_t *handle, ssize_t amt, const uv_buf_t *buffer)
	{
		Stream *stream = reinterpret_cast<Stream *>(handle->data);
		if(amt == UV_EOF)
		{
			stream->DisconnectCallback();
			delete [] buffer->base;
		}
		else if(amt < 0)
			stream->ErrorCallback(
				ENTROPY_ATTACH_TRACE(
					Net::Exception("Read Error") <<
					SystemErrorCode(error_code(-amt, system_category())) <<
					SystemError(uv_strerror(amt))
				)
			);
		else
		{
			// 2015-12-23 AMR TODO: take bits from buffer and claim ownership instead of copy
			string data(buffer->base, amt);
			delete [] buffer->base;

			stream->ReadCallback(data);
		}
	}

	void _entropy_asio_uv_stream_write_cb(uv_write_t *req, int status)
	{
		write_cb_data *data = reinterpret_cast<write_cb_data *>(req->data);
		Stream *stream = data->stream;

		delete [] data->buff->base;
		delete data->buff;
		delete data;
		delete req;

		if(status != 0)
			stream->ErrorCallback(
				ENTROPY_ATTACH_TRACE(
					Net::Exception("Write Error") <<
					SystemErrorCode(error_code(-status, system_category())) <<
					SystemError(uv_strerror(status))
				)
			);
	}

	void _entropy_asio_uv_stream_accept_cb(uv_stream_t *handle, int status)
	{
		Stream *stream = reinterpret_cast<Stream *>(handle->data);

		if(status < 0)
		{
			stream->ErrorCallback(
				ENTROPY_ATTACH_TRACE(
					Net::Exception("Accept Error") <<
					SystemErrorCode(error_code(-status, system_category())) <<
					SystemError(uv_strerror(status))
				)
			);
		}
		else
		{
			stream->AcceptCallback();
		}
	}
}
