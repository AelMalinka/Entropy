# Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
# Distributed under the terms of the GNU Affero General Public License v3

ACLOCAL_AMFLAGS = -Im4
# 2014-01-13 AMR NOTE: non-portable assignment
AM_CXXFLAGS := -I$(srcdir)/src $(AM_CXXFLAGS)

mainheadersdir = $(includedir)/Entropy
mainheaders_HEADERS = \
	src/Exception.hh \
	src/Log.hh \
	src/Application.hh \
	src/String.hh \
	src/String.impl.hh \
	src/Import.hh \
	src/Import.impl.hh \
	src/Module.hh \
	src/Module.impl.hh \
	src/Process.hh

logheadersdir = $(includedir)/Entropy/Log
logheaders_HEADERS = \
	src/Log/Init.hh \
	src/Log/Logger.hh \
	src/Log/Severity.hh

moduleheadersdir = $(includedir)/Entropy/Module
moduleheaders_HEADERS = \
	src/Module/BaseModule.hh \
	src/Module/DlModule.hh \
	src/Module/DlModule.impl.hh

netheadersdir = $(includedir)/Entropy/Net
netheaders_HEADERS = \
	src/Net/Exception.hh

netprotocolsdir = $(includedir)/Entropy/Net/Protocol
netprotocols_HEADERS = \
	src/Net/Protocol/Line.hh \
	src/Net/Protocol/Line.impl.hh

asioheadersdir = $(includedir)/Entropy/Asio
asioheaders_HEADERS = \
	src/Asio/Application.hh \
	src/Asio/Loop.hh

lib_LTLIBRARIES = libentropy.la

libentropy_la_SOURCES = \
	src/Application.cc \
	src/Module.cc \
	src/Module/BaseModule.cc \
	src/Module/DlModule.cc \
	src/Log/Init.cc \
	src/Log/Logger.cc \
	src/Log/Severity.cc \
	src/Process.cc \
	src/Asio/Application.cc \
	src/Asio/Loop.cc
libentropy_la_LDFLAGS = -version-info 0

if PYTHON
moduleheaders_HEADERS += \
	src/Module/PyModule.hh \
	src/Module/PyModule.impl.hh

pythonheadersdir = $(includedir)/Entropy/Python
pythonheaders_HEADERS = \
	src/Python/Interpreter.hh \
	src/Python/Object.hh \
	src/Python/Object.impl.hh \
	src/Python/Module.hh

libentropy_la_SOURCES += \
	src/Python/Interpreter.cc \
	src/Python/Object.cc \
	src/Python/Module.cc \
	src/Module/PyModule.cc
endif

if LIBUV
uvheadersdir = $(includedir)/Entropy/Asio/UV
uvheaders_HEADERS = \
	src/Asio/UV/Application.hh \
	src/Asio/UV/Loop.hh \
	src/Asio/UV/Handle.hh \
	src/Asio/UV/Stream.hh \
	src/Asio/UV/Tcp.hh \
	src/Asio/UV/GetAddrInfo.hh \
	src/Asio/UV/GetNameInfo.hh

libentropy_la_SOURCES += \
	src/Asio/UV/Application.cc \
	src/Asio/UV/Loop.cc \
	src/Asio/UV/Handle.cc \
	src/Asio/UV/Stream.cc \
	src/Asio/UV/Tcp.cc \
	src/Asio/UV/GetAddrInfo.cc \
	src/Asio/UV/GetNameInfo.cc
endif

if PNG
mainheaders_HEADERS += \
	src/PNG.hh

libentropy_la_SOURCES += \
	src/PNG.cc
endif

check_PROGRAMS = \
	log-trivial \
	application-run \
	module-run \
	module-import \
	module-import-twice \
	module-import-copy

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

module.so: $(srcdir)/test/Module/module.cc $(srcdir)/test/Module/interface.hh libentropy.la
	$(CXX) $(CXXFLAGS) -I $(srcdir)/src $(LIBS) -shared -fPIC -o $@ $(srcdir)/test/Module/module.cc

if PYTHON
if GTEST
check_PROGRAMS += \
	python-object \
	python-module

python_object_SOURCES = test/Python/object.cc
python_object_LDADD = -lentropy $(GTEST_LIBS)
python_object_LDFLAGS = $(PTHREAD_LDFLAGS)

python_module_SOURCES = test/Python/module.cc
python_module_LDADD = -lentropy $(GTEST_LIBS)
python_module_LDFLAGS = $(PTHREAD_LDFLAGS)
endif

check_PROGRAMS += module-import-python

module_import_python_SOURCES = test/Module/python.cc
module_import_python_LDADD = -lentropy
endif

if GTEST
check_PROGRAMS += \
	exception-init-throw \
	string-basic \
	process-basic

exception_init_throw_SOURCES = test/Exception/init-throw.cc
exception_init_throw_LDADD = -lentropy $(GTEST_LIBS)
exception_init_throw_LDFLAGS = $(PTHREAD_LDFLAGS)

string_basic_SOURCES = test/String/basic.cc
string_basic_LDADD = -lentropy $(GTEST_LIBS)
string_basic_LDFLAGS = $(PTHREAD_LDFLAGS)

process_basic_SOURCES = test/Process/basic.cc
process_basic_LDADD = -lentropy $(GTEST_LIBS)
process_basic_LDFLAGS = $(PTHREAD_LDFLAGS)

if LIBUV
check_PROGRAMS += \
	asio-uv-tcp-client \
	asio-uv-tcp-server

asio_uv_tcp_client_SOURCES = test/Asio/UV/TcpClient.cc
asio_uv_tcp_client_LDADD = -lentropy $(GTEST_LIBS) $(LIBUV_LIBS)
asio_uv_tcp_client_LDFLAGS = $(PTHREAD_LDFLAGS)

asio_uv_tcp_server_SOURCES = test/Asio/UV/TcpServer.cc
asio_uv_tcp_server_LDADD = -lentropy $(GTEST_LIBS) $(LIBUV_LIBS)
asio_uv_tcp_server_LDFLAGS = $(PTHREAD_LDFLAGS)
endif

if GMOCK
check_PROGRAMS += \
	net-protocol-line-basic \
	net-protocol-line

net_protocol_line_basic_SOURCES = test/Net/Protocol/basic.cc
net_protocol_line_basic_CXXFLAGS = -DPROTOCOL=Line -DPROTOCOL_INCLUDE=\"Net/Protocol/Line.hh\" -DMOCK_FULL=MockApplication -DMOCK_BASE=MockApplicationOnlyLine $(AM_CXXFLAGS)
net_protocol_line_basic_LDADD = -lentropy $(GMOCK_LIBS) $(GTEST_LIBS)
net_protocol_line_basic_LDFLAGS = $(PTHREAD_LDFLAGS)

net_protocol_line_SOURCES = test/Net/Protocol/line.cc
net_protocol_line_LDADD = -lentropy $(GMOCK_LIBS) $(GTEST_LIBS)
net_protocol_line_LDFLAGS = $(PTHREAD_LDFLAGS)
endif

if PNG
check_PROGRAMS += \
	png-basic

png_basic_SOURCES = test/PNG/basic.cc
png_basic_LDADD = -lentropy $(GTEST_LIBS)
png_basic_LDFLAGS = $(PTHREAD_LDFLAGS)
png_basic_DEPENDENCIES = pnglogo.png

pnglogo.png: $(srcdir)/test/PNG/pnglogo.png
	$(LN_S) $< $@
endif
endif

TESTSUITE = $(srcdir)/test/testsuite

TESTSUITE_FILES = \
	$(srcdir)/test/exception.at \
	$(srcdir)/test/log.at \
	$(srcdir)/test/application.at \
	$(srcdir)/test/net.at \
	$(srcdir)/test/Net/protocol.at \
	$(srcdir)/test/string.at \
	$(srcdir)/test/module.at \
	$(srcdir)/test/python.at \
	$(srcdir)/test/process.at \
	$(srcdir)/test/asio.at \
	$(srcdir)/test/Asio/uv.at \
	$(srcdir)/test/png.at

EXTRA_DIST = $(TESTSUITE_FILES) \
	$(srcdir)/test/testsuite.at \
	$(srcdir)/package.m4 \
	$(TESTSUITE) \
	$(srcdir)/test/atlocal.in \
	$(srcdir)/test/Module/module.cc \
	$(srcdir)/test/Module/interface.hh \
	$(srcdir)/test/Net/Protocol/Mock.hh \
	$(srcdir)/test/PNG/pnglogo.png

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
	$(RM) module.so pnglogo.png

AUTOM4TE = $(SHELL) $(srcdir)/build-aux/missing --run autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest
$(TESTSUITE): $(srcdir)/test/testsuite.at $(TESTSUITE_FILES) $(srcdir)/package.m4
	$(AUTOTEST) -I '$(srcdir)/test' -I $(srcdir) -o $@.tmp $@.at
	mv $@.tmp $@
