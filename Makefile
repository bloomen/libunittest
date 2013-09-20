VERSION = 3.4.1

PROG = libunittest
PROGVER = $(PROG)-$(VERSION)
PROGVERTAR = $(PROGVER).tar.gz
LIBNAME = $(PROG).so
VERSIONFILE = version.hpp
LIBDIR = lib
INSTALLDIR = /usr/local

CXX = g++
CXXFLAGS = -O2 -Wall -std=c++0x -pthread -fPIC -fmessage-length=0
LDFLAGS = -shared

INCDIR = include
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard src/*.cpp))
FULLVERFILE = $(INCDIR)/$(PROG)/$(VERSIONFILE)

RM = rm -f
MKDIR = mkdir -p
LN = ln -s
ECHO = echo
CP = cp
MV = mv
TAR = tar cfz
UNTAR = tar xfz
BUILDDEB = dpkg-buildpackage -rfakeroot -b

DEBRULES = debian/rules
COPYING = COPYING.txt
DISTDIR = distribution
DISTDATA = Makefile COPYING.txt README.txt CHANGES.txt include src test examples doc
BUILDDIRS = test examples/standard examples/random examples/minimal doc/doxygen
TODOSFILES = $(COPYING) README.txt CHANGES.txt doc/doxygen/doxyfile

default : $(PROG)
all : default

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I./$(INCDIR) -c $< -o $@

$(PROG) : $(OBJECTS)
	@$(MKDIR) $(LIBDIR)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $(LIBDIR)/$(LIBNAME).$(VERSION)
	@$(RM) $(LIBDIR)/$(LIBNAME)
	@$(LN) $(LIBNAME).$(VERSION) $(LIBDIR)/$(LIBNAME)

install : 
	@$(ECHO) "Installing $(PROGVER) to $(INSTALLDIR) ..."
	@$(MKDIR) $(INSTALLDIR)	
	@$(MKDIR) $(INSTALLDIR)/lib
	@$(MKDIR) $(INSTALLDIR)/include	
	@$(MKDIR) $(INSTALLDIR)/include/$(PROG)	
	@$(CP) $(LIBDIR)/$(LIBNAME).$(VERSION) $(INSTALLDIR)/lib
	@$(CP) $(INCDIR)/$(PROG)/*.hpp $(INSTALLDIR)/include/$(PROG)	
	@$(RM) $(INSTALLDIR)/lib/$(LIBNAME)
	@$(LN) $(LIBNAME).$(VERSION) $(INSTALLDIR)/lib/$(LIBNAME)

dist : version
	@$(RM) -r $(PROGVER)
	@$(MKDIR) $(PROGVER)
	@$(CP) -r $(DISTDATA) $(PROGVER)
	@$(MAKE) clean -s -C $(PROGVER)
	@for file in $(TODOSFILES); do awk 'sub("$$", "\r")' $(PROGVER)/$$file > $(PROGVER)/$$file.dos ; done
	@for file in $(TODOSFILES); do $(MV) $(PROGVER)/$$file.dos $(PROGVER)/$$file ; done
	@$(TAR) $(PROGVERTAR) $(PROGVER)
	@$(MKDIR) $(DISTDIR)
	@$(MV) $(PROGVERTAR) $(DISTDIR)
	@$(RM) -r $(PROGVER)
	@$(ECHO) "Created $(DISTDIR)/$(PROGVERTAR)"

check : clean 
	@$(ECHO) "Running check on $(PROGVER) ..."
	@$(MAKE) || exit 1
	@for dir in $(BUILDDIRS); do $(MAKE) -C $$dir || exit 1; $(MAKE) -C $$dir run || exit 1; done
	@$(ECHO) "($@) All tests passed!"

distcheck :
	@$(ECHO) "Running distribution check on $(PROGVER) ..."
	@$(MAKE) -s dist || exit 1
	@$(RM) -r $(PROGVER)
	@$(UNTAR) $(DISTDIR)/$(PROGVERTAR) || exit 1
	@$(MAKE) -C $(PROGVER) check || exit 1
	@$(MAKE) -C $(PROGVER) install INSTALLDIR=local || exit 1
	@if [ ! -f $(PROGVER)/local/lib/$(LIBNAME) ]; then exit 1; fi
	@if [ ! -f $(PROGVER)/local/include/$(PROG)/unittest.hpp ]; then exit 1; fi
	@$(RM) -r $(PROGVER)
	@$(ECHO) "($@) All tests passed!"

version :	
	@$(ECHO) "/**" > $(FULLVERFILE)
	@$(ECHO) " * @brief Auto-generated version file" >> $(FULLVERFILE)
	@$(ECHO) " * @file version.hpp" >> $(FULLVERFILE)
	@$(ECHO) " */" >> $(FULLVERFILE)
	@$(ECHO) "#pragma once" >> $(FULLVERFILE)
	@$(ECHO) "#include <string>" >> $(FULLVERFILE)
	@$(ECHO) "/**" >> $(FULLVERFILE)
	@$(ECHO) " * @brief Unit testing in C++" >> $(FULLVERFILE)
	@$(ECHO) " */" >> $(FULLVERFILE)
	@$(ECHO) "namespace unittest {" >> $(FULLVERFILE)
	@$(ECHO) "/**" >> $(FULLVERFILE)
	@$(ECHO) " * @brief The libunittest version" >> $(FULLVERFILE)
	@$(ECHO) " */" >> $(FULLVERFILE)
	@$(ECHO) "const std::string version = \"$(VERSION)\";" >> $(FULLVERFILE)
	@$(ECHO)  >> $(FULLVERFILE)
	@$(ECHO) "} // unittest" >> $(FULLVERFILE)

deb :
	@$(CP) $(COPYING) debian/copyright
	@$(ECHO) "#!/usr/bin/make -f" > $(DEBRULES)
	@$(ECHO) "# -*- makefile -*-" >> $(DEBRULES)
	@$(ECHO) "include /usr/share/cdbs/1/rules/debhelper.mk" >> $(DEBRULES)
	@$(ECHO) "CXXFLAGS = $(CXXFLAGS)" >> $(DEBRULES)
	@$(ECHO) "LDFLAGS = $(LDFLAGS)" >> $(DEBRULES)
	@$(ECHO) "include /usr/share/cdbs/1/class/makefile.mk" >> $(DEBRULES)
	@$(ECHO) "install/$(PROG)-dev::" >> $(DEBRULES)
	@$(ECHO) "	mkdir -p debian/$(PROG)-dev/usr/include/$(PROG)" >> $(DEBRULES)
	@$(ECHO) "	mkdir -p debian/$(PROG)-dev/usr/lib" >> $(DEBRULES)
	@$(ECHO) "	cp include/$(PROG)/*.hpp debian/$(PROG)-dev/usr/include/$(PROG)" >> $(DEBRULES)
	@$(ECHO) "	cp lib/$(LIBNAME).$(VERSION) debian/$(PROG)-dev/usr/lib" >> $(DEBRULES)
	@$(ECHO) "	cd debian/$(PROG)-dev/usr/lib && $(RM) -f $(LIBNAME) && ln -s $(LIBNAME).$(VERSION) $(LIBNAME)" >> $(DEBRULES)
	@$(BUILDDEB) || exit 1
	@$(RM) ../$(PROG)_$(VERSION)_*.changes
	@$(MKDIR) $(DISTDIR)
	@$(MV) ../$(PROG)-dev_$(VERSION)_*.deb $(DISTDIR)
 
clean :
	@$(ECHO) "Cleaning up ..."
	@$(RM) -r $(LIBDIR)
	@$(RM) $(OBJECTS)
	@for dir in $(BUILDDIRS); do $(MAKE) -s -C $$dir $@ ; done
 
