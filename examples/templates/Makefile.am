AM_CXXFLAGS = -I$(top_srcdir)/src/lib @AM_CXXFLAGS@
check_PROGRAMS = templates

templates_SOURCES = \
test_easy.cpp \
test_explicit.cpp

templates_LDADD = $(top_builddir)/src/lib/.libs/libunittest.a $(AM_LDFLAGS)
