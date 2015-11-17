/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#if !defined ENTROPY_NET_EXCEPTION_INC
#	define ENTROPY_NET_EXCEPTION_INC

#	include "../Exception.hh"
#	include <cstddef>

//	2013-12-24 AMR TODO: convert to std::error_code, possibly newer asio?
#	include <boost/system/error_code.hpp>

	namespace Entropy
	{
		namespace Net
		{
			ENTROPY_EXCEPTION_BASE(Exception, "Net Exception");
			ENTROPY_ERROR_INFO(SystemError, boost::system::error_code);
			ENTROPY_ERROR_INFO(BytesTransfered, std::size_t);
			ENTROPY_ERROR_INFO(BytesExpected, std::size_t);
			ENTROPY_ERROR_INFO(StringTransfered, std::string);
			ENTROPY_ERROR_INFO(StringExpected, std::string);
			ENTROPY_EXCEPTION(IncompleteTransfer, "Didn't read/write all data", Exception);
			ENTROPY_EXCEPTION_BASE(Shutdown, "TODO");
		}
	}

#endif
