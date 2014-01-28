/*	Copyright 2014 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#if !defined  ENTROPY_LOG_INC
#	define  ENTROPY_LOG_INC

#	include "Log/Init.hh"
#	include "Log/Severity.hh"
#	include "Log/Logger.hh"

	namespace Entropy
	{
		using Log::Severity;
	}

#	define ENTROPY_LOG(log, sev) BOOST_LOG_SEV(log, sev)

#endif
