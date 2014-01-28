# Copyright 2013 Michael Thomas (malinka) <malinka@entropy-development.com>
# Distributed under the terms of the GNU Lesser General Public License v3

AC_PREREQ([2.53])
m4_pattern_forbid([^AX_])
m4_pattern_forbid([^EX_])

AC_INIT([Entropy Main], [0.0.1], [bugs@entropy-development.com])
AC_CONFIG_SRCDIR([src/Exception.hh])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_TESTDIR([test])
AM_INIT_AUTOMAKE([-Wall foreign subdir-objects dist-xz no-dist-gzip])

AM_PROG_AR
LT_INIT

AC_CHECK_LIB(dl, dlopen, [], [AC_MSG_FAILURE(["failed to find -ldl"])])

AC_PROG_CXX
AC_LANG_PUSH([C++])

AC_CHECK_HEADERS(
	[	boost/asio/connect.hpp\
		boost/asio/io_service.hpp\
		boost/asio/ip/tcp.hpp\
		boost/asio/read.hpp\
		boost/asio/read_until.hpp\
		boost/asio/streambuf.hpp\
		boost/asio/write.hpp\
		boost/exception/all.hpp\
		boost/log/attributes/constant.hpp\
		boost/log/common.hpp\
		boost/log/expressions.hpp\
		boost/log/sources/severity_channel_logger.hpp\
		boost/log/support/date_time.hpp\
		boost/log/utility/setup/common_attributes.hpp\
		boost/log/utility/setup/console.hpp\
		boost/log/utility/setup/formatter_parser.hpp\
		boost/system/error_code.hpp\
		boost/throw_exception.hpp\
	],
	[],
	[AC_MSG_FAILURE([Boost is required])]
)

AX_PTHREAD
[LIBS="$PTHREAD_LIBS $LIBS"]
[CFLAGS="$PTHREAD_CFLAGS $CFLAGS"]
[CXXFLAGS="$PTHREAD_CFLAGS $CXXFLAGS"]

AC_CHECK_LIB([boost_system-mt], [main], [LIBS="-lboost_system-mt $LIBS"], [AC_MSG_FAILURE(["boost::system is required"])])
AC_CHECK_LIB([boost_log-mt], [main], [LIBS="-lboost_log-mt $LIBS"], [AC_MSG_FAILURE(["boost::log is requried"])])
AC_CHECK_LIB([boost_log_setup-mt], [main], [LIBS="-lboost_log_setup-mt $LIBS"], [AC_MSG_FAILURE(["boost::log is requried"])])

EX_WITH_GTEST
EX_FLAGS

AC_LANG_POP([C++])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile atlocal:test/atlocal.in])
AC_OUTPUT
