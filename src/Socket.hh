/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_NET_SOCKET_INC
#	define ENTROPY_NET_SOCKET_INC

#	include "Application.hh"

#	include <functional>
#	include <mutex>

#	include <boost/asio/io_service.hpp>
#	include <boost/asio/streambuf.hpp>
#	include <boost/asio/ip/tcp.hpp>

	namespace Entropy
	{
		namespace Net
		{
			class Server;

			namespace asio = boost::asio;

			// 2014-01-04 AMR TODO: named pipes
			// 2014-01-04 AMR TODO: datagrams
			class Socket
			{
				public:
					Socket(Application &);
					virtual ~Socket();
					virtual void Write(std::string &&);
					virtual void Read(const std::size_t &);
					virtual void Read(const std::string &);
					virtual void Cancel();
				protected:
					Application &application();
					asio::ip::tcp::socket &socket();
				private:
					Application &_app;
					asio::ip::tcp::socket _sock;
					std::mutex _read_lock;
					asio::streambuf _read_buff;
				friend Server;
			};
		}
	}

#endif
