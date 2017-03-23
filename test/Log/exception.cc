/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include "Log.hh"
#include "Exception.hh"

using namespace std;
using namespace Entropy;

ENTROPY_EXCEPTION_BASE(TestExceptionBase, "Test Base Exception");
ENTROPY_EXCEPTION(TestException, "Test Exception", TestExceptionBase);

int main(int, char **)
{
	Log::Logger log("Test");

	try
	{
		ENTROPY_THROW(TestException());
	}
	catch(exception &e)
	{
		log << e;
	}

	{
		TestException e;
		log << e;
	}

	try
	{
		ENTROPY_THROW(TestExceptionBase());
	}
	catch(exception &e)
	{
		log << e;
	}

	try
	{
		ENTROPY_THROW(exception());
	}
	catch(exception &e)
	{
		log << e;
	}

	try
	{
		ENTROPY_THROW(TestException("Asdf") <<
			SeverityInfo(Severity::Trace));
	}
	catch(exception &e)
	{
		log << e;
	}

	try
	{
		ENTROPY_THROW(TestException("Asdf") <<
			SeverityInfo(Severity::Info));
	}
	catch(exception &e)
	{
		log << e;
	}

	try
	{
		ENTROPY_THROW(TestExceptionBase("asdf"));
	}
	catch(Exception &e)
	{
		log << e;
	}

	return EXIT_SUCCESS;
}
