AM_CXXFLAGS = -I$(top_srcdir)/src @AM_CXXFLAGS@
check_PROGRAMS = templates

templates_SOURCES = \
test_flexible.cpp \
test_plain.cpp

templates_LDADD = $(top_builddir)/src/lib/.libs/libunittest.a $(AM_LDFLAGS)
