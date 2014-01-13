# Copyright 2013 Michael Thomas (malinka) <malinka@entropy-development.com>
# Distributed under the terms of the GNU Lesser General Public License v3

AC_PREREQ([2.53])
m4_pattern_forbid([^AX_])
m4_pattern_forbid([^EX_])

AC_INIT([Entropy Net], [0.0.1], [bugs@entropy-development.com])
AC_CONFIG_SRCDIR([src/Exception.hh])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_TESTDIR([test])
AM_INIT_AUTOMAKE([-Wall foreign subdir-objects dist-xz no-dist-gzip])

AM_PROG_AR
LT_INIT

AC_PROG_CXX
AC_LANG_PUSH([C++])

AC_CHECK_HEADERS(
	[	boost/system/error_code.hpp\
		boost/asio/buffer.hpp\
		boost/asio/io_service.hpp\
		boost/asio/basic_streambuf.hpp\
		boost/asio/ip/tcp.hpp\
		boost/asio/read.hpp\
		boost/asio/read_until.hpp\
		boost/asio/write.hpp\
	],
	[],
	[AC_MSG_FAILURE([Boost is required])]
)

AX_PTHREAD
[LIBS="$PTHREAD_LIBS $LIBS"]
[CFLAGS="$PTHREAD_CFLAGS $CFLAGS"]
[CXXFLAGS="$PTHREAD_CFLAGS $CXXFLAGS"]

AC_CHECK_LIB([boost_system-mt], [main], [LIBS="-lboost_system-mt $LIBS"], [AC_MSG_FAILURE(["boost::system is required"])])

EX_FLAGS

EX_WITH_ENTROPY
[LIBS="$ENTROPY_LIBS $LIBS"]
[LDFLAGS="$ENTROPY_LDFLAGS $LDFLAGS"]
[CPPFLAGS="$ENTROPY_CPPFLAGS $CPPFLAGS"]

AC_LANG_POP([C++])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile atlocal:test/atlocal.in])
AC_OUTPUT
