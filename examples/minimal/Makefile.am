AM_CXXFLAGS = -I$(top_srcdir)/src/lib @AM_CXXFLAGS@
check_PROGRAMS = minimal

minimal_SOURCES = \
test_minimal.cpp

minimal_LDADD = $(top_builddir)/src/lib/.libs/libunittest.a $(AM_LDFLAGS)
