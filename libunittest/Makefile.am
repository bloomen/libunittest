# additional include pathes necessary to compile the C++ library
AM_CXXFLAGS = -I$(top_srcdir)/libunittest @AM_CXXFLAGS@

# the library names to build (note we are building static libs only)
lib_LIBRARIES = libunittest.a

# where to install the headers on the system
libmylib_adir = $(includedir)/libunittest

# the list of header files that belong to the library (to be installed later)
libmylib_a_HEADERS = \
argparser.hpp \
assertions.hpp \
checkers.hpp \
environments.hpp \
formatting.hpp \
macros.hpp \
main.hpp \
random.hpp \
shortcuts.hpp \
strings.hpp \
testcase.hpp \
testcollection.hpp \
testfailure.hpp \
testlog.hpp \
testregistry.hpp \
testresults.hpp \
testrun.hpp \
teststatus.hpp \
testsuite.hpp \
tuplemap.hpp \
typetraits.hpp \
unittest.hpp \
userargs.hpp \
utilities.hpp \
version.hpp

# the sources to add to the library and to add to the source distribution
libmylib_a_SOURCES = \
$(libmylib_a_HEADERS) \
argparser.cpp \
environments.cpp \
formatting.cpp \
main.cpp \
random.cpp \
testcollection.cpp \
testfailure.cpp \
testlog.cpp \
testresults.cpp \
testrun.cpp \
testsuite.cpp \
userargs.cpp \
utilities.cpp 
