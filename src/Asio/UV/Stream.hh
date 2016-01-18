/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASIO_UV_STREAM_INC
#	define ENTROPY_ASIO_UV_STREAM_INC

#	include "Handle.hh"

#	include <functional>
#	include <deque>
#	include <memory>

#	include "../../Net/Exception.hh"
#	include "GetAddrInfo.hh"

	extern "C" {
		void _entropy_asio_uv_stream_alloc_cb(uv_handle_t *, size_t, uv_buf_t *);
		void _entropy_asio_uv_stream_read_cb(uv_stream_t *, ssize_t, const uv_buf_t *);
		void _entropy_asio_uv_stream_write_cb(uv_write_t *, int);
		void _entropy_asio_uv_stream_accept_cb(uv_stream_t *, int);
	}

	namespace Entropy
	{
		namespace Asio
		{
			namespace UV
			{
				// 2016-01-12 AMR TODO: cleanup udp, move tcp to UV::Tcp
				class Stream :
					public Handle
				{
					public:
						virtual ~Stream();
						void Connect(const std::string &, const std::string &);
						void Listen(const std::string &, const std::string &);
						void Disconnect();
						void Write(const std::string &);
						bool isReadable() const;
						bool isWritable() const;
						virtual const struct sockaddr Socket() const = 0;
					protected:
						virtual void connect(const struct sockaddr *) = 0;
						virtual void bind(const struct sockaddr *) = 0;
						virtual std::shared_ptr<Stream> accept() = 0;
						virtual int sock_type() = 0;
					protected:
						Stream(Asio::Loop &, uv_stream_t *, const std::function<void(Stream &, const std::string &)> &, const std::function<void(const Net::Exception &)> &);
						uv_stream_t *stream();
						const uv_stream_t *stream()const;
						void read_start();
						void read_stop();
						std::function<void(Stream &, const std::string &)> &ReadCb();
						std::function<void(const Net::Exception &)> &ErrorCb();
						const std::function<void(Stream &, const std::string &)> &ReadCb() const;
						const std::function<void(const Net::Exception &)> &ErrorCb() const;
					protected:
						void ReadCallback(const std::string &);
						void ErrorCallback(const Net::Exception &);
						void ListenInfoCallback(struct addrinfo *);
						void ConnectInfoCallback(struct addrinfo *);
						void AcceptCallback();
						virtual void ConnectCallback() = 0;
						virtual void DisconnectCallback() = 0;
					private:
						uv_stream_t *_handle;
						GetAddrInfo *_lookup;
						std::deque<std::shared_ptr<Stream>> _clients;
						std::function<void(Stream &, const std::string &)> _read_cb;
						std::function<void(const Net::Exception &)> _error_cb;
					friend void ::_entropy_asio_uv_stream_alloc_cb(uv_handle_t *, size_t, uv_buf_t *);
					friend void ::_entropy_asio_uv_stream_read_cb(uv_stream_t *, ssize_t, const uv_buf_t *);
					friend void ::_entropy_asio_uv_stream_write_cb(uv_write_t *, int);
					friend void ::_entropy_asio_uv_stream_accept_cb(uv_stream_t *, int);
				};
			}
		}
	}

#endif
