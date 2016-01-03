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

Stream::Stream(Loop &loop, uv_stream_t *handle, const function<void(Stream &, const string &)> &cb, const function<void(const Net::Exception &)> &err)
	: Handle(loop, reinterpret_cast<uv_handle_t *>(handle)), _handle(handle), _read_cb(cb), _error_cb(err)
{}

Stream::~Stream()
{
	read_stop();
}

void Stream::Connect(const string &h, const string &s)
{
	uv_getaddrinfo_t *req = new uv_getaddrinfo_t;
	info_cb_data *data = new info_cb_data;

	req->data = data;

	data->stream = this;
	data->hints = new struct addrinfo;

	memset(data->hints, 0, sizeof(struct addrinfo));
	data->hints->ai_family = AF_UNSPEC;
	data->hints->ai_flags = AI_PASSIVE;
	data->hints->ai_socktype = sock_type();

	int ret = uv_getaddrinfo(Owner().Handle(), req, _entropy_asio_uv_stream_info_cb, h.data(), s.data(), data->hints);
	if(ret < 0)
		ENTROPY_THROW(
			GeneralFailure("uv_getaddrinfo failed") <<
			SystemErrorCode(error_code(-ret, system_category())) <<
			SystemError(uv_strerror(ret))
		);
}

void Stream::Disconnect()
{
	read_stop();
}

void Stream::Write(const string &s)
{
	uv_write_t *req = new uv_write_t;
	req->data = new write_cb_data;

	write_cb_data *data = reinterpret_cast<write_cb_data *>(req->data);

	data->stream = this;
	data->buff = new uv_buf_t;
	data->buff->len = s.size();
	
	data->buff->base = new char[s.size()];
	memcpy(data->buff->base, s.data(), s.size());

	int ret = uv_write(req, stream(), data->buff, 1, _entropy_asio_uv_stream_write_cb);
	if(ret < 0)
		ENTROPY_THROW(
			GeneralFailure("uv_write failed") <<
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

void Stream::ReadCallback(Stream &, const string &data)
{
	_read_cb(*this, data);
}

void Stream::ErrorCallback(const Net::Exception &err)
{
	_error_cb(err);
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
	int ret = uv_read_start(_handle, _entropy_asio_uv_stream_alloc_cb, _entropy_asio_uv_stream_read_cb);
	if(ret < 0)
		ENTROPY_THROW(
			GeneralFailure("uv_read_start failed") <<
			SystemErrorCode(error_code(-ret, system_category())) <<
			SystemError(uv_strerror(ret))
		);
}

void Stream::read_stop()
{
	int ret = uv_read_stop(_handle);
	if(ret < 0)
		ENTROPY_THROW(
			GeneralFailure("uv_read_stop failed") <<
			SystemErrorCode(error_code(-ret, system_category())) <<
			SystemError(uv_strerror(ret))
		);
}

extern "C" {
	void _entropy_asio_uv_stream_alloc_cb(uv_handle_t *, size_t size, uv_buf_t *buffer)
	{
		buffer->base = new char[size];
		buffer->len = size;
	}

	// 2016-01-03 AMR TODO: attempt to connect to more than just the first response
	void _entropy_asio_uv_stream_info_cb(uv_getaddrinfo_t *req, int status, struct addrinfo *info)
	{
		info_cb_data *data = reinterpret_cast<info_cb_data *>(req->data);
		Stream *stream = data->stream;

		delete data->hints;
		delete data;
		delete req;

		if(status != 0)
			stream->ErrorCallback(
				ENTROPY_ATTACH_TRACE(
					Net::Exception("Lookup Error") <<
					SystemErrorCode(error_code(-status, system_category())) <<
					SystemError(uv_strerror(status))
				)
			);
		else
		{
			stream->connect(info->ai_addr);
		}

		uv_freeaddrinfo(info);
	}

	void _entropy_asio_uv_stream_read_cb(uv_stream_t *handle, ssize_t amt, const uv_buf_t *buffer)
	{
		Stream *stream = reinterpret_cast<Stream *>(handle->data);
		if(amt == UV_EOF)
		{}	// 2015-12-23 AMR NOTE: no error here, move along
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

			stream->ReadCallback(*stream, data);
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
}
