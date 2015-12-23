/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_NET_PROTOCOL_LINE_INC
#	define ENTROPY_NET_PROTOCOL_LINE_INC

#	include <string>
#	include <map>
#	include "../Exception.hh"

	namespace Entropy
	{
		namespace Net
		{
			namespace Protocol
			{
				template<typename Application, typename Socket>
				class Line
				{
					public:
						explicit Line(Application &);
						Line(Application &, const std::string &delim);
						virtual ~Line();
						void onConnect(Socket &);
						void onDisconnect(Socket &);
						void onData(Socket &, const std::string &);
						void onError(const Net::Exception &);
					private:
						Application &_app;
						std::map<Socket, std::string> _buffs;
						const std::string _delim;
						static constexpr const std::size_t _buffer_size = ENTROPY_NET_BUFFER_SIZE;
				};
			}
		}
	}

#	include "Line.impl.hh"

#endif
