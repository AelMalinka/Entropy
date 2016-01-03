/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASIO_UV_TCP_INC
#	define ENTROPY_ASIO_UV_TCP_INC

#	include "Loop.hh"
#	include "Stream.hh"

	extern "C" {
		void _entropy_asio_uv_tcp_connect_cb(uv_connect_t *, int);
	}

	namespace Entropy
	{
		namespace Asio
		{
			namespace UV
			{
				class Tcp :
					public Stream
				{
					public:
						Tcp(Loop &, const std::function<void(Stream &)> &, const std::function<void(Stream &, const std::string &)> &, const std::function<void(const Net::Exception &)> &);
						~Tcp();
					protected:
						void ConnectCallback(Stream &);
					protected:
						void connect(const struct sockaddr *);
						int sock_type();
					private:
						uv_tcp_t _handle;
						std::function<void(Stream &)> _connect_cb;
						friend void ::_entropy_asio_uv_tcp_connect_cb(uv_connect_t *, int);
				};
			}
		}
	}

#endif
