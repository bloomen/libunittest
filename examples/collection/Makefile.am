AM_CXXFLAGS = -I$(top_srcdir)/src/lib @AM_CXXFLAGS@
check_PROGRAMS = collection

collection_SOURCES = \
test_collection.cpp

collection_LDADD = $(top_builddir)/src/lib/.libs/libunittest.a $(AM_LDFLAGS)
