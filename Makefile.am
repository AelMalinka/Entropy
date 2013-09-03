ACLOCAL_AMFLAGS = -I m4

mainheadersdir = $(includedir)/Entropy
mainheaders_HEADERS = src/Exception.hh

testdir = $(builddir)/tests
check_PROGRAMS = exception

exception_SOURCES = test/Exception.cc
exception_CXXFLAGS = -I$(srcdir)/src $(AM_CXXFLAGS)

TESTS = exception
