AM_CXXFLAGS = -I$(top_srcdir)/src/lib @AM_CXXFLAGS@
check_PROGRAMS = random

random_SOURCES = \
test_random.cpp

random_LDADD = $(top_builddir)/src/lib/.libs/libunittest.a $(AM_LDFLAGS)
