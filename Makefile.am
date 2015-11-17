# Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
# Distributed under the terms of the GNU Lesser General Public License v3

ACLOCAL_AMFLAGS = -I m4
# 2014-01-13 AMR NOTE: non-portable assignment
AM_CXXFLAGS := -I $(srcdir)/src $(AM_CXXFLAGS)

mainheadersdir = $(includedir)/Entropy
mainheaders_HEADERS = src/Exception.hh \
	src/Application.hh \
	src/Import.hh src/Import.impl.hh src/Module.hh src/Module.impl.hh

logheadersdir = $(includedir)/Entropy/Log
logheaders_HEADERS = src/Log.hh src/Log/Init.hh src/Log/Logger.hh src/Log/Severity.hh

moduleheadersdir = $(includedir)/Module
moduleheaders_HEADERS = src/Module/BaseModule.hh \
	src/Module/DlModule.hh src/Module/DlModule.impl.hh \
	src/Module/PyModule.hh src/Module/PyModule.impl.hh

netheadersdir = $(includedir)/Entropy/Net
netheaders_HEADERS = src/Net/Exception.hh src/Net/Application.hh src/Net/Socket.hh \
	src/Net/Client.hh src/Net/Server.hh src/Net/Protocol.hh

netprotocolsdir = $(includedir)/Entropy/Net/Protocols
netprotocols_HEADERS = src/Net/Protocols/Line.hh

lib_LTLIBRARIES = libentropy.la

libentropy_la_SOURCES = src/Application.cc src/Module.cc \
	src/Module/BaseModule.cc src/Module/DlModule.cc src/Module/PyModule.cc \
	src/Log/Init.cc src/Log/Logger.cc src/Log/Severity.cc \
	src/Net/Application.cc src/Net/Socket.cc src/Net/Protocol.cc src/Net/Client.cc src/Net/Server.cc src/Net/Protocols/Line.cc
libentropy_la_LDFLAGS = -version-info 0

check_PROGRAMS = log-trivial \
	application-run \
	module-run module-import module-import-twice module-import-copy module-import-python \
	net-protocol-line net-protocol-crlf-line

log_trivial_SOURCES = test/Log/trivial.cc
log_trivial_LDADD = -lentropy

application_run_SOURCES = test/Application/run.cc
application_run_LDADD = -lentropy

module_run_SOURCES = test/Module/run.cc
module_run_LDADD = -lentropy
module_run_DEPENDENCIES = module.so

module_import_SOURCES = test/Module/import.cc
module_import_LDADD = -lentropy
module_import_DEPENDENCIES = module.so

module_import_twice_SOURCES = test/Module/import-twice.cc
module_import_twice_LDADD = -lentropy
module_import_twice_DEPENDENCIES = module.so

module_import_copy_SOURCES = test/Module/import-copy.cc
module_import_copy_LDADD = -lentropy
module_import_copy_DEPENDENCIES = module.so

module_import_python_SOURCES = test/Module/python.cc
module_import_python_LDADD = -lentropy
module_import_python_DEPENDENCIES = module.py

net_protocol_line_SOURCES = test/Net/Protocol/line.cc
net_protocol_line_LDADD = -lentropy

net_protocol_crlf_line_SOURCES = test/Net/Protocol/line.cc
net_protocol_crlf_line_CPPFLAGS = -D_DELIM=\"\r\n\"
net_protocol_crlf_line_LDADD = -lentropy

module.so: $(srcdir)/test/Module/module.cc $(srcdir)/test/Module/interface.hh libentropy.la
	$(CXX) $(CXXFLAGS) -I $(srcdir)/src $(LIBS) -shared -fPIC -o $@ $(srcdir)/test/Module/module.cc

module.py: $(srcdir)/test/Module/module.py
	cp $< $@

clean-local: module-clean
.PHONY: module-clean
module-clean:
	rm -f module.so

if GTEST
check_PROGRAMS += exception-init-throw

exception_init_throw_SOURCES = test/Exception/init-throw.cc
exception_init_throw_LDADD = $(GTEST_LIBS)
exception_init_throw_LDFLAGS = $(PTHREAD_LDFLAGS)
endif

TESTSUITE = $(srcdir)/test/testsuite
TESTSUITE_FILES = $(srcdir)/test/log.at $(srcdir)/test/exception.at $(srcdir)/test/application.at \
	$(srcdir)/test/module.at $(srcdir)/test/net.at \
	$(srcdir)/test/Net/protocol.at
EXTRA_DIST = $(TESTSUITE_FILES) $(srcdir)/test/testsuite.at $(srcdir)/package.m4 $(TESTSUITE) $(srcdir)/test/atlocal.in \
	$(srcdir)/test/Module/module.cc $(srcdir)/test/Module/interface.hh $(srcdir)/test/Module/module.py

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
