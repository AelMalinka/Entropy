/*	Copyright 2014 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#if !defined ENTROPY_LOG_SEVERITY_INC
#	define ENTROPY_LOG_SEVERITY_INC

#	include "Init.hh"

#	include <ostream>
#	include <cstdlib>

#	include <boost/log/expressions/keyword.hpp>

	namespace Entropy
	{
		namespace Log
		{
			enum class Severity : std::size_t
			{
				Trace,
				Debug,
				Info,
				Warning,
				Error,
				Critical,
				Fatal
			};

			std::ostream &operator << (std::ostream &, const Severity &);

			BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", Severity)
		}
	}

#endif
