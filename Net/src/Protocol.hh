/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_NET_PROTOCOL_INC
#	define ENTROPY_NET_PROTOCOL_INC

#	include "Application.hh"
#	include "Socket.hh"

	namespace Entropy
	{
		namespace Net
		{
			class Protocol :
				public Application
			{
				public:
					Protocol();
					virtual ~Protocol();
				protected:
					virtual void expecting(Socket &, const std::size_t &);
					virtual void expecting(Socket &, const std::string &);
			};
		}
	}

#endif
