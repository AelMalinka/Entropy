/*	Copyright 2014 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#if !defined ENTROPY_NET_SERVER_INC
#	define ENTROPY_NET_SERVER_INC

#	include "Socket.hh"

#	include <list>
#	include <mutex>

	namespace Entropy
	{
		namespace Net
		{
			class Server
			{
				public:
					Server(Application &, const std::string &);
					Server(Application &, const std::string &, const std::string &);
					virtual ~Server();
				protected:
					void listen(const std::string &host, const std::string &port);
				private:
					Application &_app;
					std::list<Socket> _sockets;
					asio::ip::tcp::acceptor _acceptor;
					std::mutex _mutex;
					asio::io_service::work _work;
			};
		}
	}

#endif
