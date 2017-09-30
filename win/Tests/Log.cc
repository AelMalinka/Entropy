/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Tests
{
	TEST_CLASS(Log)
	{
		TEST_METHOD(Trivial)
		{
			Entropy::Log::Logger lg;

			ENTROPY_LOG(lg, Entropy::Severity::Info) << "This is a log line";
		}
	};
}