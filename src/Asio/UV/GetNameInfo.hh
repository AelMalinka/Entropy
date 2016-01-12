/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASIO_UV_GETNAMEINFO_INC
#	define ENTROPY_ASIO_UV_GETNAMEINFO_INC

#	include "Stream.hh"
#	include <functional>

	extern "C" {
		void _entropy_asio_uv_getnameinfo_cb(uv_getnameinfo_t *, int, const char *, const char *);
	}

	namespace Entropy
	{
		namespace Asio
		{
			namespace UV
			{
				class GetNameInfo
				{
					public:
						GetNameInfo(Loop &, const std::function<void(const std::string &, const std::string &)> &, const Stream &);
						~GetNameInfo();
					protected:
						void callback(const std::string &, const std::string &);
					private:
						uv_getnameinfo_t _req;
						std::function<void(const std::string &, const std::string &)> _cb;
					friend void ::_entropy_asio_uv_getnameinfo_cb(uv_getnameinfo_t *, int, const char *, const char *);
				};
			}
		}
	}

#endif
