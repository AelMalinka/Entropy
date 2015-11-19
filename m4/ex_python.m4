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
	AS_IF([test "x$with_python" != xno], [
		m4_foreach(ver, [
			[python],
			[python3],
			[python2],
			[python3.5],
			[python3.4],
			[python3.3],
			[python2.7]],
		[
			[python_bin=]ver
			AC_PATH_PROG([PYTHON], ver)
		])
		AC_ARG_VAR([PYTHON], [python interpreter])
		python_version=`$PYTHON -V 2>&1 | $GREP "^Python " | $SED 's/Python //'`
		AS_IF([test `echo $python_version | $SED -e 's,\..*\..*,,'` -le 2], [[
			PYTHON_CPPFLAGS=-I`$PYTHON -c "from distutils import sysconfig; print sysconfig.get_config_vars('CONFINCLUDEPY')[0]"`
		]], [[
			PYTHON_CPPFLAGS=-I`$PYTHON -c "from distutils import sysconfig; print(sysconfig.get_config_vars('CONFINCLUDEPY'))"`
		]])
		[old_flags=$CPPFLAGS; CPPFLAGS=$PYTHON_CPPFLAGS]
		EX_CHECK_LIBRARY([PYTHON], [Python.h], $python_bin)
		[CPPFLAGS=$old_flags]
	])
	AS_IF([test "x$with_python" != xcheck -a "x$with_python" != xno -a "x$PYTHON_LIBS" == x], [AC_MSG_FAILURE(["python requested but not found"])])
	AM_CONDITIONAL([PYTHON], [test "x$PYTHON_LIBS" != x])
])
