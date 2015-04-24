AM_CXXFLAGS = -I$(top_srcdir)/src/lib @AM_CXXFLAGS@
check_PROGRAMS = explicit

explicit_SOURCES = \
test_something.cpp \
test_whatever.cpp

explicit_LDADD = $(top_builddir)/src/lib/.libs/libunittest.a $(AM_LDFLAGS)
