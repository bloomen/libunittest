AM_CXXFLAGS = -I$(top_srcdir)/src @AM_CXXFLAGS@

check_PROGRAMS = flexible

flexible_SOURCES = \
test_something.cpp \
test_whatever.cpp
flexible_LDADD = $(top_builddir)/src/lib/.libs/libunittest.a $(AM_LDFLAGS)
