/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Tests
{
	ENTROPY_EXCEPTION_BASE(TestExceptionBase, "Text Exception Base");
	ENTROPY_EXCEPTION(TestException, "Text Exception", TestExceptionBase);
	ENTROPY_EXCEPTION(TestException2, "Text Exception 2", TestException);

	TEST_CLASS(Exception)
	{
		public:
			TEST_METHOD(Throw) {
				using namespace Entropy;

				TestExceptionBase a;
				TestExceptionBase b("Error Description");
				TestException c;
				TestException d("Description");

				Assert::ExpectException<ExceptionBase>([&](){ throw a; });
				Assert::ExpectException<ExceptionBase>([&](){ throw b; });
				Assert::ExpectException<ExceptionBase>([&](){ throw c; });
				Assert::ExpectException<ExceptionBase>([&](){ throw d; });
				Assert::ExpectException<Entropy::Exception>([&](){ throw a; });
				Assert::ExpectException<Entropy::Exception>([&](){ throw a; });
				Assert::ExpectException<Entropy::Exception>([&](){ throw c; });
				Assert::ExpectException<Entropy::Exception>([&](){ throw d; });
				Assert::ExpectException<TestExceptionBase>([&](){ throw a; });
				Assert::ExpectException<TestExceptionBase>([&](){ throw b; });
				Assert::ExpectException<TestExceptionBase>([&](){ throw c; });
				Assert::ExpectException<TestExceptionBase>([&](){ throw d; });
				Assert::ExpectException<TestException>([&](){ throw c; });
				Assert::ExpectException<TestException>([&](){ throw d; });
			}

			TEST_METHOD(MultipleInheritance) {
				TestException a;
				TestException2 b;

				Assert::ExpectException<TestException>([&](){ throw a; });
				Assert::ExpectException<TestException>([&](){ throw b; });
				Assert::ExpectException<TestException2>([&](){ throw b; });
			}

			TEST_METHOD(EntropyThrow) {
				using namespace Entropy;

				try
				{
					ENTROPY_THROW(TestException("Entropy Throw, has"));
				}
				catch (TestException &e)
				{
					Assert::IsTrue(e.has<throw_function>());
					Assert::IsTrue(e.has<throw_file>());
					Assert::IsTrue(e.has<throw_line>());
					Assert::IsFalse(e.has<SystemError>());
					Assert::AreEqual(58, e.get<throw_line>());
				}
			}
	};
}