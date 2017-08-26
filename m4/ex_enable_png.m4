dnl Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
dnl Distributed under the terms of the GNU General Public License v3

AC_DEFUN([EX_ENABLE_PNG], [
	AC_ARG_ENABLE([png],
		[AS_HELP_STRING([--enable-png], [support for png image format])],
		[enable_png=$enableval],
		[enable_png=check]
	)

	AS_IF([test "x$enable_png" != "xno"],
		[
			test "x$enable_png" != "xyes" -a "x$enable_png" != xcheck && LDFLAGS="${LDFLAGS} -L$enable_png"
			EX_CHECK_LIBRARY([PNG], ["png.h"], [png])
		]
	)
	AM_CONDITIONAL([PNG], [test "x$PNG_LIBS" != "x"])
	AS_IF([test "x$enable_png" != "xcheck" -a "x$enable_png" != "xno" -a "x$PNG_LIBS" = "x"], [AC_MSG_FAILURE(["--enable-png: libpng not found"])])
])
