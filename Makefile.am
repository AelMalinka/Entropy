# Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
# Distributed under the terms of the GNU Affero General Public License v3

ACLOCAL_AMFLAGS = -Im4
AM_CPPFLAGS = -I$(srcdir)/src

mainheadersdir = $(includedir)/Entropy
mainheaders_HEADERS = \
	src/Application.hh \
	src/DefaultedList.hh \
	src/DefaultedList.impl.hh \
	src/Event.hh \
	src/Exception.hh \
	src/Exception.impl.hh \
	src/Import.hh \
	src/Import.impl.hh \
	src/Log.hh \
	src/Module.hh \
	src/Module.impl.hh \
	src/PolymorphicList.hh \
	src/PolymorphicList.impl.hh \
	src/PolymorphicListIterator.hh \
	src/PolymorphicListIterator.impl.hh \
	src/Process.hh \
	src/SharedData.hh \
	src/SharedData.impl.hh \
	src/String.hh

logheadersdir = $(includedir)/Entropy/Log
logheaders_HEADERS = \
	src/Log/Init.hh \
	src/Log/Logger.hh \
	src/Log/Severity.hh

moduleheadersdir = $(includedir)/Entropy/Module
moduleheaders_HEADERS = \
	src/Module/DlModule.hh \
	src/Module/DlModule.impl.hh \
	src/Module/Exception.hh

lib_LTLIBRARIES = libentropy.la

libentropy_la_SOURCES = \
	src/Application.cc \
	src/Event.cc \
	src/Exception.cc \
	src/Module.cc \
	src/Process.cc \
	src/String.cc \
	src/Log/Init.cc \
	src/Log/Logger.cc \
	src/Log/Severity.cc \
	src/Module/DlModule.cc
libentropy_la_LDFLAGS = -version-info 0

if PYTHON
moduleheaders_HEADERS += \
	src/Module/PyModule.hh \
	src/Module/PyModule.impl.hh

pythonheadersdir = $(includedir)/Entropy/Python
pythonheaders_HEADERS = \
	src/Python/Interpreter.hh \
	src/Python/Module.hh \
	src/Python/Object.hh \
	src/Python/Object.impl.hh

libentropy_la_SOURCES += \
	src/Module/PyModule.cc \
	src/Python/Interpreter.cc \
	src/Python/Module.cc \
	src/Python/Object.cc
endif

if PNG
mainheaders_HEADERS += \
	src/PNG.hh

libentropy_la_SOURCES += \
	src/PNG.cc
endif

check_PROGRAMS = \
	log-trivial \
	log-exception \
	application-run \
	module-run \
	module-import \
	module-import-twice \
	module-import-copy

log_trivial_SOURCES = test/Log/trivial.cc
log_trivial_LDADD = libentropy.la

log_exception_SOURCES = test/Log/exception.cc
log_exception_LDADD = libentropy.la

application_run_SOURCES = test/Application/run.cc
application_run_LDADD = libentropy.la

module_run_SOURCES = test/Module/run.cc
module_run_LDADD = libentropy.la
module_run_DEPENDENCIES = module.so

module_import_SOURCES = test/Module/import.cc
module_import_LDADD = libentropy.la
module_import_DEPENDENCIES = module.so

module_import_twice_SOURCES = test/Module/import-twice.cc
module_import_twice_LDADD = libentropy.la
module_import_twice_DEPENDENCIES = module.so

module_import_copy_SOURCES = test/Module/import-copy.cc
module_import_copy_LDADD = libentropy.la
module_import_copy_DEPENDENCIES = module.so

module.so: $(srcdir)/test/Module/module.cc $(srcdir)/test/Module/interface.hh libentropy.la
	$(CXX) $(CXXFLAGS) -I. $(AM_CPPFLAGS) $(LIBS) -shared -fPIC -o $@ $(srcdir)/test/Module/module.cc

if GTEST
check_PROGRAMS += \
	event-basic \
	exception-init-throw \
	string-basic \
	process-basic \
	utility-defaulted-list \
	utility-polymorphic-list-iterator \
	utility-polymorphic-list \
	utility-shared-data

event_basic_SOURCES = test/Event/basic.cc
event_basic_LDADD = libentropy.la $(GTEST_LIBS)
event_basic_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_CPPFLAGS)
event_basic_LDFLAGS = $(GTEST_LDFLAGS) $(PTHREAD_LDFLAGS)

exception_init_throw_SOURCES = test/Exception/init-throw.cc
exception_init_throw_LDADD = libentropy.la $(GTEST_LIBS)
exception_init_throw_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_CPPFLAGS)
exception_init_throw_LDFLAGS = $(GTEST_LDFLAGS) $(PTHREAD_LDFLAGS)

string_basic_SOURCES = test/String/basic.cc
string_basic_LDADD = libentropy.la $(GTEST_LIBS)
string_basic_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_CPPFLAGS)
string_basic_LDFLAGS = $(GTEST_LDFLAGS) $(PTHREAD_LDFLAGS)

process_basic_SOURCES = test/Process/basic.cc
process_basic_LDADD = libentropy.la $(GTEST_LIBS)
process_basic_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_CPPFLAGS)
process_basic_LDFLAGS = $(GTEST_LDFLAGS) $(PTHREAD_LDFLAGS)

utility_defaulted_list_SOURCES = test/utility/defaulted-list.cc
utility_defaulted_list_LDADD = libentropy.la $(GTEST_LIBS)
utility_defaulted_list_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_CPPFLAGS)
utility_defaulted_list_LDFLAGS = $(GTEST_LDFLAGS) $(PTHREAD_LDFLAGS)

utility_polymorphic_list_iterator_SOURCES = test/utility/polymorphic-list-iterator.cc
utility_polymorphic_list_iterator_LDADD = libentropy.la $(GTEST_LIBS)
utility_polymorphic_list_iterator_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_CPPFLAGS)
utility_polymorphic_list_iterator_LDFLAGS = $(GTEST_LDFLAGS) $(PTHREAD_LDFLAGS)

utility_polymorphic_list_SOURCES = test/utility/polymorphic-list.cc
utility_polymorphic_list_LDADD = libentropy.la $(GTEST_LIBS)
utility_polymorphic_list_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_CPPFLAGS)
utility_polymorphic_list_LDFLAGS = $(GTEST_LDFLAGS) $(PTHREAD_LDFLAGS)

utility_shared_data_SOURCES = test/utility/shared-data.cc
utility_shared_data_LDADD = libentropy.la $(GTEST_LIBS)
utility_shared_data_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_CPPFLAGS)
utility_shared_data_LDFLAGS = $(GTEST_LDFLAGS) $(PTHREAD_LDFLAGS)

if PYTHON
check_PROGRAMS += \
	python-object \
	python-module

python_object_SOURCES = test/Python/object.cc
python_object_LDADD = libentropy.la $(GTEST_LIBS)
python_object_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_CPPFLAGS)
python_object_LDFLAGS = $(GTEST_LDFLAGS) $(PTHREAD_LDFLAGS)

python_module_SOURCES = test/Python/module.cc
python_module_LDADD = libentropy.la $(GTEST_LIBS)
python_module_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_CPPFLAGS)
python_module_LDFLAGS = $(GTEST_LDFLAGS) $(PTHREAD_LDFLAGS)
endif

if PNG
check_PROGRAMS += \
	png-basic

png_basic_SOURCES = test/PNG/basic.cc
png_basic_LDADD = libentropy.la $(GTEST_LIBS)
png_basic_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_CPPFLAGS)
png_basic_LDFLAGS = $(GTEST_LDFLAGS) $(PTHREAD_LDFLAGS)
png_basic_DEPENDENCIES = pnglogo.png

pnglogo.png: $(srcdir)/test/PNG/pnglogo.png
	$(LN_S) $< $@
endif
endif

if PYTHON
check_PROGRAMS += module-import-python

module_import_python_SOURCES = test/Module/python.cc
module_import_python_LDADD = libentropy.la
endif

TESTSUITE = $(srcdir)/test/testsuite

TESTSUITE_FILES = \
	$(srcdir)/test/application.at \
	$(srcdir)/test/event.at \
	$(srcdir)/test/exception.at \
	$(srcdir)/test/log.at \
	$(srcdir)/test/module.at \
	$(srcdir)/test/png.at \
	$(srcdir)/test/process.at \
	$(srcdir)/test/python.at \
	$(srcdir)/test/string.at \
	$(srcdir)/test/utility.at

EXTRA_DIST = $(TESTSUITE_FILES) \
	$(srcdir)/test/testsuite.at \
	$(srcdir)/package.m4 \
	$(TESTSUITE) \
	$(srcdir)/test/atlocal.in \
	$(srcdir)/test/Module/module.cc \
	$(srcdir)/test/Module/interface.hh \
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
	$(RM) atlocal module.so pnglogo.png

AUTOM4TE = $(SHELL) $(srcdir)/build-aux/missing --run autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest
$(TESTSUITE): $(srcdir)/test/testsuite.at $(TESTSUITE_FILES) $(srcdir)/package.m4
	$(AUTOTEST) -I '$(srcdir)/test' -I $(srcdir) -o $@.tmp $@.at
	mv $@.tmp $@
