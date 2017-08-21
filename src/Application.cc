/*	Copyright 2010 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Pulbic License v3
*/

#include "Application.hh"

#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>

#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>

using namespace Entropy;
using namespace std;

Application::Application()
	: _argc(-1), _argv(nullptr)
{}

Application::Application(const int c, char *v[])
	: _argc(c), _argv(v)
{}

Application::~Application() = default;

void Application::addFileLog(const string &file)
{
	using namespace Entropy::Log;
	using namespace boost::log;
	using namespace boost::log::expressions;

	using boost::posix_time::ptime;

	auto sink = add_file_log(
		keywords::file_name = file,
		keywords::filter = (
			#if defined DEBUG
				severity >= Severity::Debug
			#else
				severity >= Severity::Info
			#endif
		),
		keywords::format = (
			stream <<
				format_date_time<ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f") << ": " <<
				attr<attributes::current_process_id::value_type>("ProcessID") << ": " <<
				attr<attributes::current_thread_id::value_type>("ThreadID") << ": " <<
				#if defined DEBUG
					attr<string>("Function") << ": " <<
					attr<string>("File") << "(" <<
					attr<int>("Line") << "): " <<
				#endif
				attr<string>("Channel") << ": " <<
				attr<Severity>("Severity") << ": " <<
				message
		),
		keywords::auto_flush = (
			true
		)
	);

	core::get()->add_sink(sink);
}

void Application::addFileLog(const string &file, const Severity &sev)
{
	using namespace Entropy::Log;
	using namespace boost::log;
	using namespace boost::log::expressions;

	using boost::posix_time::ptime;

	auto sink = add_file_log(
		keywords::file_name = file,
		keywords::filter = (
			severity >= sev
		),
		keywords::format = (
			stream <<
				format_date_time<ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f") << ": " <<
				attr<attributes::current_process_id::value_type>("ProcessID") << ": " <<
				attr<attributes::current_thread_id::value_type>("ThreadID") << ": " <<
				#if defined DEBUG
					attr<string>("Function") << ": " <<
					attr<string>("File") << "(" <<
					attr<int>("Line") << "): " <<
				#endif
				attr<string>("Channel") << ": " <<
				attr<Severity>("Severity") << ": " <<
				message
		),
		keywords::auto_flush = (
			true
		)
	);

	core::get()->add_sink(sink);
}

const int &Application::ArgC()
{
	return _argc;
}

char **Application::ArgV()
{
	return _argv;
}
