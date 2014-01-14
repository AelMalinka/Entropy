# Copyright 2013 (c) Michael Thomas <aelmalinka@gmail.com>
#
# Copying and distribution of this file, with or without modification, are
# permitted in any medium without royalty provided the copyright notice
# and this notice are preserved. This file is offered as-is, without any
# warranty.

AC_DEFUN([EX_WITH_ENTROPY], [
	CPPFLAGS_save="$CPPFLAGS"
	CXXFLAGS_save="$CXXFLAGS"
	LDFLAGS_save="$LDFLAGS"
	AC_ARG_WITH([entropy],
		[AS_HELP_STRING([--with-entropy], [location to look for libentropy-main.so])],
		[with_entropy=$withval],
		[with_entropy=check]
	)

	ENTROPY_LIBS=
	CXXFLAGS="$CXXFLAGS -Wno-pedantic"
	test "x$with_entropy" != xcheck && LDFLAGS="-L${with_entropy}/lib"
	AC_CHECK_LIB([entropy-main], [main], [
			AC_SUBST([ENTROPY_LIBS], ["-lentropy-main"])
			AC_SUBST([ENTROPY_LDFLAGS], ["$LDFLAGS"])
		],
		AC_MSG_FAILURE(["--with-entropy: entropy-main not found"])
	)
	ENTROPY_CPPFLAGS=
	test "x$with_entropy" != xcheck && CPPFLAGS="-I${with_entropy}/include"
	AC_CHECK_HEADER([Entropy/Exception.hh], [
			AC_SUBST([ENTROPY_CPPFLAGS], ["$CPPFLAGS"])
		],
		AC_MSG_FAILURE(["--with-entropy: Entropy/Exception.hh not found"])
	)
	CPPFLAGS="$CPPFLAGS_save"
	CXXFLAGS="$CXXFLAGS_save"
	LDFLAGS="$LDFLAGS_save"
])
