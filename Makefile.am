ACLOCAL_AMFLAGS = -I m4
#2013-10-11 AMR XXX: non-portable assignment
AM_CXXFLAGS := -I $(srcdir)/src $(AM_CXXFLAGS)

mainheadersdir = $(includedir)/Entropy/Net
mainheaders_HEADERS = src/Exception.hh src/Application.hh src/Protocol.hh src/Socket.hh src/Protocols/Line.hh

lib_LTLIBRARIES = libentropy-net.la

libentropy_net_la_SOURCES = src/Application.cc src/Socket.cc src/Protocol.cc src/Protocols/Line.cc src/Client.cc src/Server.cc

check_PROGRAMS = socket-echo

socket_echo_SOURCES = test/Socket/echo.cc
socket_echo_LDADD = -lentropy-net

TESTSUITE = $(srcdir)/test/testsuite
TESTSUITE_FILES = $(srcdir)/test/socket.at
TESTSUITE_SRC_FILES = $(srcdir)/test/Socket/init.cc
EXTRA_DIST = $(TESTSUITE) $(TESTSUITE_FILES) $(TESTSUITE_SRC_FILES)\
	$(srcdir)/test/testsuite.at $(srcdir)/package.m4 $(srcdir)/test/atlocal.in

$(srcdir)/package.m4: $(srcdir)/configure.ac
	:; {\
		echo '# Signature of the current package. (auto-generated)' && \
		echo 'm4_define([AT_PACKAGE_NAME],' && \
		echo '  [$(PACKAGE_NAME)])' && \
		echo 'm4_define([AT_PACKAGE_TARNAME],' && \
		echo '  [$(PACKAGE_TARNAME)])' && \
		echo 'm4_define([AT_PACKAGE_VERSION],' && \
		echo '  [$(PACKAGE_VERSION)])' && \
		echo 'm4_define([AT_PACKAGE_STRING],' && \
		echo '  [$(PACKAGE_STRING)])' && \
		echo 'm4_define([AT_PACKAGE_BUGREPORT],' && \
		echo '  [$(PACKAGE_BUGREPORT)])'; \
		echo 'm4_define([AT_PACKAGE_URL],' && \
		echo '  [$(PACKAGE_URL)])'; \
	} >'$(srcdir)/package.m4'

check-local: test/atconfig atlocal $(TESTSUITE) $(check_PROGRAMS)
	$(SHELL) '$(TESTSUITE)' AUTOTEST_PATH='$(shell pwd)' $(TESTSUITEFLAGS)

clean-local:
	test ! -f '$(TESTSUITE)' || \
		$(SHELL) '$(TESTSUITE)' --clean

AUTOM4TE = $(SHELL) $(srcdir)/build-aux/missing --run autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest
$(TESTSUITE): $(srcdir)/test/testsuite.at $(TESTSUITE_FILES) $(srcdir)/package.m4
	$(AUTOTEST) -I '$(srcdir)/test' -I $(srcdir) -o $@.tmp $@.at
	mv $@.tmp $@
