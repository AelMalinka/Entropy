/*	Copyright 2012 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Exception.hh"
#include <gtest/gtest.h>

#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif

using namespace std;
using namespace Entropy;
using namespace testing;

namespace {
	ENTROPY_EXCEPTION_BASE(TestExceptionBase, "Test Base Exception");
	ENTROPY_EXCEPTION(TestException, "Test Exception", TestExceptionBase);

	TEST(ExceptionTest, ThrowBase) {
		TestExceptionBase a;
		TestExceptionBase b("Error Description");
		EXPECT_THROW(throw a, ExceptionBase);
		EXPECT_THROW(throw b, ExceptionBase);
		EXPECT_THROW(throw a, Exception);
		EXPECT_THROW(throw b, Exception);
	}

	TEST(ExceptionTest, Throw) {
		TestException a;
		TestException b("Description");
		EXPECT_THROW(throw a, Exception);
		EXPECT_THROW(throw b, Exception);
		EXPECT_THROW(throw a, ExceptionBase);
		EXPECT_THROW(throw b, ExceptionBase);
		EXPECT_THROW(throw a, Exception);
		EXPECT_THROW(throw b, Exception);
	}

	TEST(ExceptionTest, ENTROPY_THROW) {
		EXPECT_THROW(ENTROPY_THROW(TestException("Entropy Throw")), TestException);

		try
		{
			ENTROPY_THROW(TestException("Entropy Throw, has"));
		}
		catch(TestException &e)
		{
			EXPECT_TRUE(e.has<throw_function>());
			EXPECT_TRUE(e.has<throw_file>());
			EXPECT_TRUE(e.has<throw_line>());
#			ifdef HAVE_BACKTRACE
				EXPECT_TRUE(e.has<BackTrace>());
#			endif

			EXPECT_FALSE(e.has<SystemError>());

			EXPECT_EQ(string(e.get<throw_function>()), "virtual void {anonymous}::ExceptionTest_ENTROPY_THROW_Test::TestBody()"s);
			EXPECT_EQ(e.get<throw_line>(), 45);
		}
	}

	TEST(ExceptionTest, ENTROPY_THROW_NonEntropyException) {
		EXPECT_THROW(ENTROPY_THROW(logic_error("Entropy Throw, logic")), logic_error);

		try
		{
			ENTROPY_THROW(logic_error("Entropy Throw, logic, has"));
		}
		catch(logic_error &e)
		{
			EXPECT_NE(::boost::get_error_info<throw_function>(e), nullptr);
			EXPECT_NE(::boost::get_error_info<throw_file>(e), nullptr);
			EXPECT_NE(::boost::get_error_info<throw_line>(e), nullptr);
#			ifdef HAVE_BACKTRACE
				EXPECT_NE(::boost::get_error_info<BackTrace>(e), nullptr);
#			endif

			EXPECT_EQ(::boost::get_error_info<SystemError>(e), nullptr);

			EXPECT_EQ(string(*::boost::get_error_info<throw_function>(e)), "virtual void {anonymous}::ExceptionTest_ENTROPY_THROW_NonEntropyException_Test::TestBody()"s);
			EXPECT_EQ(*::boost::get_error_info<throw_line>(e), 68);
		}
	}
}
