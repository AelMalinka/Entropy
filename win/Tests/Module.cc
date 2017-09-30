/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Entropy;
using namespace Entropy::Test;

namespace Tests
{
	TEST_CLASS(Module)
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