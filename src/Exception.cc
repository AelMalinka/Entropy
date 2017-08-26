/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Exception.hh"

#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif

#ifdef HAVE_BACKTRACE
#	include <execinfo.h>
#endif

using namespace Entropy;
using namespace std;

ExceptionBase::ExceptionBase() = default;

ExceptionBase::ExceptionBase(const std::string &Type) :
	boost::exception(), m_type(Type), m_desc(), m_what(Type)
{}

ExceptionBase::ExceptionBase(const std::string &Type, const std::string &Desc) :
	boost::exception(), m_type(Type), m_desc(Desc), m_what(((Desc != "") ? Type + ": " + Desc : Type))
{}

ExceptionBase::~ExceptionBase() noexcept = default;

const char *ExceptionBase::what() const noexcept
{
	return m_what.c_str();
}

Exception::Exception(const std::string &Type)
	: std::exception(), ExceptionBase(Type)
{}

Exception::Exception(const std::string &Type, const std::string &Desc)
	: std::exception(), ExceptionBase(Type, Desc)
{}

Exception::~Exception() noexcept = default;

const char *Exception::what() const noexcept
{
	return ExceptionBase::what();
}

namespace Entropy {
	void AttachTrace(boost::exception &e)
	{
#		ifdef HAVE_BACKTRACE
			try
			{
				const int size = 100;
				void *buffer[size];
				char **strings;

				int count = backtrace(buffer, size);
				strings = backtrace_symbols(buffer, count);

				string trace;
			
				for(auto x = 1; x < count; x++)
					trace += string(strings[x]) + "\n";
				trace = trace.substr(0, trace.size() - 1);

				e << BackTrace(trace);
			}
			catch(...)
			{}
#		else
			(void)e;
#		endif
	}
}
