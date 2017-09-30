#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Tests
{
	class Application :
		public Entropy::Application
	{
		public:
			Application();
			~Application() = default;
			void operator () ();
	};

	ENTROPY_EXCEPTION_BASE(TestFailure, "Test Failure");
	ENTROPY_EXCEPTION_BASE(TestSuccess, "Test Success");

	TEST_CLASS(ApplicationTests)
	{
		public:
			TEST_METHOD(Run)
			{
				Application app;

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

	Application::Application()
		: Entropy::Application()
	{}

	void Application::operator () ()
	{
		throw TestSuccess();
	}
}