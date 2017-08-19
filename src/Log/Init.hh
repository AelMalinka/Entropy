/*	Copyright 2014 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_LOG_INIT_INC
#	define ENTROPY_LOG_INIT_INC

#	ifndef _WIN32
#		define BOOST_ALL_DYN_LINK
#	else
		// 2017-08-18 AMR HACK: on windows w/ vs 2017 ending up with a mismatch in win api version
		// 2017-08-18 AMR NOTE: for now use win 10 api
#		define BOOST_USE_WINAPI_VERSION 0x0A00
#	endif

#	include <boost/log/common.hpp>

	namespace Entropy
	{
		namespace Log
		{
			namespace detail
			{
				struct Initializer
				{
					Initializer();
				};

				static const Initializer Init;
			}
		}
	}

#endif
