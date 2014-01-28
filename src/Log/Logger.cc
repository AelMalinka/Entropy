/*	Copyright 2014 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#include "Logger.hh"

#include <boost/log/attributes/constant.hpp>

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
