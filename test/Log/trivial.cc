/*	Copyright 2014 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>

#include "Log.hh"

using namespace std;
using namespace Entropy;

int main(int, char **)
{
	{
		Log::Logger lg;

		ENTROPY_LOG(lg, Severity::Info) << "This is a log line";
		ENTROPY_LOG(lg, Severity::Trace) << "This is a skipped log line";
	}

	{
		Log::Logger lg(Severity::Error);

		BOOST_LOG(lg) << "This is a error line";
		ENTROPY_LOG(lg, Severity::Trace) << "This is a skipped line";
	}

	{
		Log::Logger lg("Test");

		ENTROPY_LOG(lg, Severity::Info) << "This is a 'Test' line";
		ENTROPY_LOG(lg, Severity::Trace) << "This is a skipped line";
	}

	{
		Log::Logger lg("Test", Severity::Error);

		BOOST_LOG(lg) << "This is an error 'Test' line";
		ENTROPY_LOG(lg, Severity::Trace) << "This is a skipped line";
	}

	return EXIT_SUCCESS;
}

