/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#if !defined ENTROPY_NET_APPLICATION_INC
#	define ENTROPY_NET_APPLICATION_INC

#	include "Exception.hh"

#	include <boost/asio/io_service.hpp>

	namespace Entropy
	{
		namespace Net
		{
			namespace asio = boost::asio;

			class Socket;

			class Application
			{
				public:
					Application();
					virtual ~Application();
					virtual void onConnect(Socket &) = 0;
					virtual void onData(Socket &, std::string &&) = 0;
					virtual void onError(const Net::Exception &);
					asio::io_service &Io();
				private:
					asio::io_service _io;
			};
		}
	}

#endif
