#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Entropy;
using namespace Entropy::Test;

namespace Tests
{
	TEST_CLASS(ModuleTests)
	{
		public:
			TEST_METHOD(Basic)
			{
				Import<Interface> i("TestModule.dll");

				Assert::AreEqual(i->Name(), "Windows Module"s);
				Assert::AreEqual(i->Value(), 12u);
			}
	};
}