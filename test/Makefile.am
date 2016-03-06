AM_CXXFLAGS = -I$(top_srcdir)/src/lib @AM_CXXFLAGS@
check_PROGRAMS = unittest

unittest_SOURCES = \
main.cpp \
test_argparser.cpp \
test_assertions.cpp \
test_checkers.cpp \
test_context.cpp \
test_formatting.cpp \
test_macros_explicit.cpp \
test_macros_easy.cpp \
test_macros_easy_tpl.cpp \
test_misc.cpp \
test_random.cpp \
test_testrun.cpp \
test_userargs.cpp \
test_utilities.cpp \
test_quote.cpp

unittest_LDADD = $(top_builddir)/src/lib/.libs/libunittest.a $(AM_LDFLAGS)
