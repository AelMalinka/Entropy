/*	Copyright 2014 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Logger.hh"

#include <boost/log/attributes/constant.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>

using namespace Entropy::Log;
using namespace std;
using namespace boost::log;

Logger::~Logger() = default;

Logger::Logger()
	: severity_channel_logger_mt(keywords::channel = "Application", keywords::severity = Severity::Info)
{}

Logger::Logger(const string &chan)
	: severity_channel_logger_mt(keywords::channel = chan, keywords::severity = Severity::Info)
{}

Logger::Logger(const Severity &sev)
	: severity_channel_logger_mt(keywords::channel = "Application", keywords::severity = sev)
{}

Logger::Logger(const string &chan, const Severity &sev)
	: severity_channel_logger_mt(keywords::channel = chan, keywords::severity = sev)
{}

Logger &Logger::operator << (const exception &e)
{
	using ::Entropy::throw_function;
	using ::Entropy::throw_file;
	using ::Entropy::throw_line;
	using ::boost::get_error_info;

	auto s = get_error_info<SeverityInfo>(e);
	Severity sev = (s) ? *s : Severity::Fatal;

	record rec = this->open_record(keywords::severity = sev);
	if(rec)
	{
		record_ostream strm(rec);

		auto w = get_error_info<throw_function>(e);
		auto f = get_error_info<throw_file>(e);
		auto l = get_error_info<throw_line>(e);

		if(w) strm << add_value("Function", *w);
		if(f) strm << add_value("File", *f);
		if(l) strm << add_value("Line", *l);

		strm << e.what() << flush;

		this->push_record(move(rec));
	}

	return *this;
}
