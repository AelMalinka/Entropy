/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_NET_EXCEPTION_INC
#	define ENTROPY_NET_EXCEPTION_INC

#	ifndef ENTROPY_NET_BUFFER_SIZE
#		define ENTROPY_NET_BUFFER_SIZE 1024
#	endif

#	include "../Exception.hh"
#	include <cstddef>
#	include <system_error>

	namespace Entropy
	{
		namespace Net
		{
			ENTROPY_EXCEPTION_BASE(Exception, "Basic Network Exception");
			ENTROPY_ERROR_INFO(SystemError, std::error_code);
		}
	}

#endif
