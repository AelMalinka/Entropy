ACLOCAL_AMFLAGS = -I m4
AM_CXXFLAGS := -I $(srcdir)/src $(AM_CXXFLAGS)

mainheadersdir = $(includedir)/Entropy
mainheaders_HEADERS = src/Exception.hh src/Application.hh

lib_LTLIBRARIES = libEntropy.la

libEntropy_la_SOURCES = src/Application.cc
libEntropy_la_LDFLAGS = -version-info 0

check_PROGRAMS = 

if GTEST
check_PROGRAMS += exception-init-throw application-run

exception_init_throw_SOURCES = test/Exception/init-throw.cc
exception_init_throw_LDADD = -lgtest_main -lgtest
exception_init_throw_LDFLAGS = -pthread

application_run_SOURCES = test/Application/run.cc
application_run_LDADD = -lgtest_main -lgtest -lEntropy
application_run_LDFLAGS = -pthread
endif

TESTSUITE = $(srcdir)/test/testsuite
TESTSUITE_FILES = $(srcdir)/test/exception.at $(srcdir)/test/application.at
EXTRA_DIST = $(TESTSUITE_FILES) $(srcdir)/test/testsuite.at $(srcdir)/package.m4 $(TESTSUITE) $(srcdir)/test/atlocal.in

$(srcdir)/package.m4: $(top_srcdir)/configure.ac
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

check-local: test/atconfig atlocal $(TESTSUITE)
	$(SHELL) '$(TESTSUITE)' AUTOTEST_PATH='$(shell pwd)' $(TESTSUITEFLAGS)

clean-local:
	test ! -f '$(TESTSUITE)' || \
		$(SHELL) '$(TESTSUITE)' --clean

AUTOM4TE = $(SHELL) $(srcdir)/build-aux/missing --run autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest
$(TESTSUITE): $(srcdir)/test/testsuite.at $(TESTSUITE_FILES) $(srcdir)/package.m4
	$(AUTOTEST) -I '$(srcdir)/test' -I $(srcdir) -o $@.tmp $@.at
	mv $@.tmp $@
