#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Tests
{
	TEST_CLASS(Event)
	{
		public:
			TEST_METHOD(Construct)
			{
				Entropy::Event e(10u);

				Assert::AreEqual(e.Id(), 10u);
			}
	};
}