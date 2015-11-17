/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_NET_PROTOCOL_LINE_INC
#	define ENTROPY_NET_PROTOCOL_LINE_INC

#	include "../Protocol.hh"

	namespace Entropy
	{
		namespace Net
		{
			namespace Protocols
			{
				class Line :
					public Net::Protocol
				{
					public:
						Line();
						explicit Line(const std::string &delim);
						virtual ~Line();
						virtual bool onMessage(Socket &, std::string &&) = 0;
						virtual void onConnect(Socket &);
						void onData(Socket &, std::string &&);
					private:
						std::string _delim;
				};
			}
		}
	}

#endif
