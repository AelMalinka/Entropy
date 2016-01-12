/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASIO_UV_GETADDRINFO_INC
#	define ENTROPY_ASIO_UV_GETADDRINFO_INC

#	include "Loop.hh"
#	include <functional>

	extern "C" {
		void _entropy_asio_uv_getaddrinfo_cb(uv_getaddrinfo_t *, int, struct addrinfo *);
	}

	namespace Entropy
	{
		namespace Asio
		{
			namespace UV
			{
				class GetAddrInfo
				{
					public:
						GetAddrInfo(Loop &, const std::function<void (struct addrinfo *)> &, const std::string &, const std::string &, int);
						~GetAddrInfo();
					protected:
						void callback(struct addrinfo *);
					private:
						uv_getaddrinfo_t _req;
						std::function<void (struct addrinfo *)> _cb;
						struct addrinfo _hints;
					friend void ::_entropy_asio_uv_getaddrinfo_cb(uv_getaddrinfo_t *, int, struct addrinfo *);
				};
			}
		}
	}

#endif
