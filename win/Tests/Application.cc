#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Tests
{
	class TestApplication :
		public Entropy::Application
	{
		public:
			TestApplication();
			~TestApplication() = default;
			void operator () ();
	};

	ENTROPY_EXCEPTION_BASE(TestFailure, "Test Failure");
	ENTROPY_EXCEPTION_BASE(TestSuccess, "Test Success");

	TEST_CLASS(Application)
	{
		public:
			TEST_METHOD(Run)
			{
				TestApplication app;

				try
				{
					app();
				}
				catch (TestSuccess)
				{}
				catch (TestFailure)
				{
					Assert::Fail(L"Test Failed");
				}
			}
	};

	TestApplication::TestApplication()
		: Entropy::Application()
	{}

	void TestApplication::operator () ()
	{
		throw TestSuccess();
	}
}