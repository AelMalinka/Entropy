/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASIO_UV_STREAM_INC
#	define ENTROPY_ASIO_UV_STREAM_INC

#	include "Handle.hh"
#	include "../../Net/Exception.hh"
#	include <functional>

	extern "C" {
		void _entropy_asio_uv_stream_alloc_cb(uv_handle_t *, size_t, uv_buf_t *);
		void _entropy_asio_uv_stream_info_cb(uv_getaddrinfo_t *, int, struct addrinfo *);
		void _entropy_asio_uv_stream_read_cb(uv_stream_t *, ssize_t, const uv_buf_t *);
		void _entropy_asio_uv_stream_write_cb(uv_write_t *, int);
	}

	namespace Entropy
	{
		namespace Asio
		{
			namespace UV
			{
				class Stream :
					public Handle
				{
					public:
						virtual ~Stream();
						void Connect(const std::string &, const std::string &);
						void Disconnect();
						void Write(const std::string &);
						bool isReadable() const;
						bool isWritable() const;
					protected:
						void ReadCallback(Stream &, const std::string &);
						void ErrorCallback(const Net::Exception &);
					protected:
						Stream(Loop &, uv_stream_t *, const std::function<void(Stream &, const std::string &)> &, const std::function<void(const Net::Exception &)> &);
						uv_stream_t *stream();
						const uv_stream_t *stream()const;
						void read_start();
						void read_stop();
					protected:
						virtual void connect(const struct sockaddr *) = 0;
						virtual int sock_type() = 0;
					private:
						uv_stream_t *_handle;
						std::function<void(Stream &, const std::string &)> _read_cb;
						std::function<void(const Net::Exception &)> _error_cb;
					friend void ::_entropy_asio_uv_stream_alloc_cb(uv_handle_t *, size_t, uv_buf_t *);
					friend void ::_entropy_asio_uv_stream_info_cb(uv_getaddrinfo_t *, int, struct addrinfo *);
					friend void ::_entropy_asio_uv_stream_read_cb(uv_stream_t *, ssize_t, const uv_buf_t *);
					friend void ::_entropy_asio_uv_stream_write_cb(uv_write_t *, int);
				};
			}
		}
	}

#endif
