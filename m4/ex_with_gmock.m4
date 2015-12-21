dnl Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
dnl Distributed under the terms of the GNU General Public License v3

AC_DEFUN([EX_WITH_GMOCK], [
	AC_ARG_WITH([gmock],
		[AS_HELP_STRING([--with-gmock], [support for google mock framework, required for some tests])],
		[with_gmock=$withval],
		[with_gmock=check]
	)

	AS_IF([test "x$with_gmock" != xno],
		[
			test "x$with_gmock" != xyes -a "x$with_gmock" != xcheck && LDFLAGS="${LDFLAGS} -L$with_gmock"
			EX_CHECK_LIBRARY([GMOCK], ["gmock/gmock.h"], [gmock], [], [
				AS_IF([test "x$with_gmock" != xcheck], [
					AC_MSG_FAILURE(["--with-gmock: gmock not found"])
				])
			])
			AC_CHECK_LIB([gmock_main], [main], [
					GMOCK_LIBS="-lgmock_main $GMOCK_LIBS"
				], [AS_IF([test "x$with_gmock" != xcheck], [
					AC_MSG_FAILURE(["--with-gmock: gmock_main not found"])
				])
			])
		]
	)
	AM_CONDITIONAL([GMOCK], [test "x$GMOCK_LIBS" != x])
])
