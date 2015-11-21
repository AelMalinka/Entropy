dnl Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
dnl Distributed under the terms of the GNU Affero General Public License v3

AC_DEFUN([EX_PYTHON], [
	AC_REQUIRE([AC_PROG_SED])
	AC_REQUIRE([AC_PROG_GREP])
	AC_ARG_WITH([python],
		[AS_HELP_STRING([--with-python], [support for PyModule using python])],
		[with_python=$withval],
		[with_python=check]
	)
	dnl 2015-11-21 AMR TODO: add version check and check python as well
	AS_IF([test "x$with_python" != xno], [
		m4_foreach(ver, [
			[python3],
			[python3.5],
			[python3.4],
			[python3.3]],
		[
			AS_IF([test "x$PYTHON_LIBS" == x], [
				[python_bin=]ver
				AC_PATH_PROG([PYTHON], ver)
				[PYTHON_CPPFLAGS=-I`$PYTHON -c "from distutils import sysconfig; print(sysconfig.get_config_vars('CONFINCLUDEPY')[0])"`
				old_flags=$CPPFLAGS; CPPFLAGS=$PYTHON_CPPFLAGS]
				EX_CHECK_LIBRARY([PYTHON], [Python.h], $python_bin)
				[CPPFLAGS=$old_flags]
			])
		])
	])
	AC_ARG_VAR([PYTHON], [python interpreter])
	AS_IF([test "x$with_python" != xcheck -a "x$with_python" != xno -a "x$PYTHON_LIBS" == x], [AC_MSG_FAILURE(["python requested but not found"])])
	AM_CONDITIONAL([PYTHON], [test "x$PYTHON_LIBS" != x])
])
