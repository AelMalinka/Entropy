/*	Copyright 2014 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined  ENTROPY_LOG_INC
#	define  ENTROPY_LOG_INC

#	include "Log/Init.hh"
#	include "Log/Severity.hh"
#	include "Log/Logger.hh"

#	include <boost/log/utility/manipulators/add_value.hpp>

	namespace Entropy
	{
		using Log::Severity;
		using Log::SeverityInfo;
	}

#	define ENTROPY_LOG(logger, sev) \
		BOOST_LOG_SEV(logger, sev) << \
		::boost::log::add_value("Function", BOOST_CURRENT_FUNCTION) << \
		::boost::log::add_value("File", __FILE__) << \
		::boost::log::add_value("Line", __LINE__)

#	include "Exception.hh"

#endif
