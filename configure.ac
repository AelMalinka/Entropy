# Copyright 2013 Michael Thomas (malinka) <malinka@entropy-development.com>
# Distributed under the terms of the GNU Lesser General Public License v3

AC_PREREQ([2.53])
m4_pattern_forbid([^AX_])

AC_INIT([Entropy Main], [0.0.1], [bugs@entropy-development.com])
AC_CONFIG_SRCDIR([src/Exception.hh])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects dist-xz no-dist-gzip])
AC_PROG_CXX
AC_LANG_PUSH([C++])
AX_APPEND_COMPILE_FLAGS([-Wall -Wextra -Werror -pedantic-errors], [CXXFLAGS])
AC_CONFIG_HEADERS([config.h])
AX_CXX_COMPILE_STDCXX_11([noext])
AC_LANG_POP([C++])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
