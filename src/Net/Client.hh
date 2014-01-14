/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_NET_CLIENT_INC
#	define ENTROPY_NET_CLIENT_INC

#	include "Socket.hh"

	namespace Entropy
	{
		namespace Net
		{
			class Client :
				public Socket
			{
				public:
					Client(Application &, const std::string &);
					Client(Application &, const std::string &, const std::string &);
					virtual ~Client();
				private:
					void connect(const std::string &, const std::string &);
			};
		}
	}

#endif
