VERSION = 3.3.0dev

PROG = libunittest
PROGVER = $(PROG)-$(VERSION)
LIBNAME = $(PROG).so
VERSIONFILE = version.hpp
LIBDIR = lib
INSTALLDIR = /usr/local

UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
CXX = clang++ -stdlib=libc++ -U__STRICT_ANSI__
else
CXX = g++
endif

CXXFLAGS = -O2 -Wall -std=c++0x -pthread -fPIC
LDFLAGS = -shared

INCDIR = include
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard src/*.cpp))

RM = rm -f
MKDIR = mkdir -p
LN = ln -s
ECHO = echo
CP = cp
TAR = tar cfz
UNTAR = tar xfz
MV = mv

DISTDIR = distribution
DISTDATA = Makefile COPYING.txt README.txt CHANGES.txt include src test examples doc
BUILDDIRS = test examples/standard examples/random examples/minimal doc

default : $(PROG)
all : default

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I./$(INCDIR) -c $< -o $@

$(PROG) : version $(OBJECTS)
	@$(MKDIR) $(LIBDIR)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $(LIBDIR)/$(LIBNAME).$(VERSION)
	@$(RM) $(LIBDIR)/$(LIBNAME)
	@$(LN) $(LIBNAME).$(VERSION) $(LIBDIR)/$(LIBNAME)

install : version
	@$(ECHO) "Installing $(PROGVER) to $(INSTALLDIR) ..."
	@$(MKDIR) $(INSTALLDIR)	
	@$(MKDIR) $(INSTALLDIR)/lib
	@$(MKDIR) $(INSTALLDIR)/include	
	@$(MKDIR) $(INSTALLDIR)/include/$(PROG)	
	@$(CP) $(LIBDIR)/$(LIBNAME).$(VERSION) $(INSTALLDIR)/lib
	@$(CP) $(INCDIR)/$(PROG)/*.hpp $(INSTALLDIR)/include/$(PROG)	
	@$(RM) $(INSTALLDIR)/lib/$(LIBNAME)
	@$(LN) $(LIBNAME).$(VERSION) $(INSTALLDIR)/lib/$(LIBNAME)

dist : clean version
	@$(RM) -r $(PROGVER)
	@$(MKDIR) $(PROGVER)
	@$(CP) -r $(DISTDATA) $(PROGVER)
	@for dir in $(BUILDDIRS); do $(MAKE) -s -C $(PROGVER)/$$dir clean; done
	@$(TAR) $(PROGVER).tar.gz $(PROGVER)
	@$(MKDIR) $(DISTDIR)
	@$(MV) $(PROGVER).tar.gz $(DISTDIR)
	@$(RM) -r $(PROGVER)
	@$(ECHO) "Created $(DISTDIR)/$(PROGVER).tar.gz"

check : clean version
	@$(ECHO) "Running check on $(PROGVER) ..."
	@$(MAKE) || exit 1
	@for dir in $(BUILDDIRS); do $(MAKE) -C $$dir || exit 1; $(MAKE) -C $$dir run || exit 1; done
	@$(ECHO) "($@) All tests passed!"

distcheck :
	@$(ECHO) "Running distribution check on $(PROGVER) ..."
	@$(MAKE) -s dist || exit 1
	@$(RM) -r $(PROGVER)
	@$(UNTAR) $(DISTDIR)/$(PROGVER).tar.gz || exit 1
	@$(MAKE) -C $(PROGVER) check || exit 1
	@$(MAKE) -C $(PROGVER) install INSTALLDIR=local || exit 1
	@if [ ! -f $(PROGVER)/local/lib/libunittest.so ]; then exit 1; fi
	@if [ ! -f $(PROGVER)/local/include/libunittest/unittest.hpp ]; then exit 1; fi
	@$(RM) -r $(PROGVER)
	@$(ECHO) "($@) All tests passed!"

version :	
	@$(ECHO) "/**\n * @brief Auto-generated version file. Do not edit!\n * @file version.hpp\n */\n#pragma once\n#include<string>\n/**\n * @brief Unit testing in C++\n */\nnamespace unittest {\n/**\n * @brief The libunittest version\n */\nconst std::string version = \"$(VERSION)\";\n\n} // unittest" > $(INCDIR)/$(PROG)/$(VERSIONFILE)

clean :
	@$(ECHO) "Cleaning up ..."
	@$(RM) -r $(LIBDIR)
	@$(RM) $(OBJECTS)
	@for dir in $(BUILDDIRS); do $(MAKE) -s -C $$dir $@ ; done
