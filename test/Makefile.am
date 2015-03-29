AM_CXXFLAGS = -I$(top_srcdir)/src @AM_CXXFLAGS@
check_PROGRAMS = unittest

unittest_SOURCES = \
main.cpp \
test_argparser.cpp \
test_assertions.cpp \
test_checkers.cpp \
test_context.cpp \
test_formatting.cpp \
test_macros.cpp \
test_misc.cpp \
test_random.cpp \
test_testrun.cpp \
test_typetraits.cpp \
test_userargs.cpp \
test_utilities.cpp

unittest_LDADD = $(top_builddir)/src/lib/.libs/libunittest.a $(AM_LDFLAGS)
