/*	Copyright 2014 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_LOG_INIT_INC
#	define ENTROPY_LOG_INIT_INC

#	define BOOST_ALL_DYN_LINK

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
