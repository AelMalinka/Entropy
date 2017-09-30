#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Entropy;

namespace Tests
{
	TEST_CLASS(LogTests)
	{
		TEST_METHOD(Trivial)
		{
			Log::Logger lg;

			ENTROPY_LOG(lg, Severity::Info) << "This is a log line";
		}
	};
}