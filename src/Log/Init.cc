/*	Copyright 2014 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Init.hh"
#include "Severity.hh"

#include <iostream>

#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>

#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>

using namespace Entropy::Log;
using namespace std;
using namespace boost::log;

detail::Initializer::Initializer()
{
	using boost::log::expressions::stream;
	using boost::log::expressions::format_date_time;
	using boost::log::expressions::message;
	using boost::log::expressions::attr;
	using boost::posix_time::ptime;

	core::get()->remove_all_sinks();
	add_common_attributes();

	auto sink = add_console_log(
		clog,
		keywords::filter = (
			#if defined DEBUG
				severity >= Severity::Debug
			#else
				severity >= Severity::Info
			#endif
		),
		keywords::format = (
			stream <<
				format_date_time<ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f") << ": "<<
				attr<attributes::current_process_id::value_type>("ProcessID") << ": " <<
				attr<attributes::current_thread_id::value_type>("ThreadID") << ": " <<
				attr<string>("Channel") << ": " <<
				attr<Severity>("Severity") << ": " <<
#				if defined DEBUG
					attr<string>("Function") << ": " <<
					attr<string>("File") << "(" <<
					attr<int>("Line") << "): " <<
#				endif
				message
		)
	);

	core::get()->add_sink(sink);
}
