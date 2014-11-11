include mk/common.mk
MAJOR = 7
MINOR = 0
PATCH = 2
VERSION = $(MAJOR).$(MINOR).$(PATCH)

PROG = libunittest
PROGVER = $(PROG)-$(VERSION)
PROGVERTAR = $(PROGVER).tar.gz
VERSIONFILE = version.hpp
INSTALLDIR = /usr/local

ifeq ($(shell uname), Darwin)
	LIBEXT = dylib
	LIBNAME = $(PROG).$(LIBEXT)
	SONAME = $(PROG).$(MAJOR).$(LIBEXT)
	REALNAME = $(PROG).$(VERSION).$(LIBEXT)
    LDFLAGS = -arch x86_64 -dynamiclib -install_name $(REALNAME) -compatibility_version $(MAJOR).$(MINOR).0 -current_version $(VERSION)
else
	LIBEXT = so
	LIBNAME = $(PROG).$(LIBEXT)
	SONAME = $(LIBNAME).$(MAJOR)
	REALNAME = $(LIBNAME).$(VERSION)
    LDFLAGS = -shared -Wl,-soname,$(SONAME)
endif

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard src/*.cpp))
FULLVERFILE = $(INCDIR)/$(PROG)/$(VERSIONFILE)

MKDIR = mkdir -p
LN = ln -s
ECHO = echo
CP = cp
CD = cd
MV = mv
TAR = tar cfz
UNTAR = tar xfz

COPYING = COPYING.txt
CHANGES = CHANGES.txt
DISTDIR = distribution
DISTDATA = Makefile COPYING.txt README.txt $(CHANGES) include src test examples doc mk
BUILDDIRS = test examples/flexible examples/collection examples/random examples/minimal examples/templates doc/doxygen
TODOSFILES = $(COPYING) README.txt $(CHANGES) examples/README.txt doc/doxygen/doxyfile

.PHONY : default all install dist version versioncheck check distcheck upload clean

default : $(LIBDIR)/$(REALNAME)
all : default

$(LIBDIR)/$(REALNAME) : $(LIBDIR) $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $(LIBDIR)/$(REALNAME)
	@$(RM) $(LIBDIR)/$(SONAME)
	@$(RM) $(LIBDIR)/$(LIBNAME)
	@$(CD) $(LIBDIR); $(LN) $(REALNAME) $(SONAME)
	@$(CD) $(LIBDIR); $(LN) $(SONAME) $(LIBNAME)

$(LIBDIR) :
	@$(MKDIR) $(LIBDIR)

install : 
	@$(ECHO) "Installing $(PROGVER) to $(INSTALLDIR) ..."
	@$(MKDIR) $(INSTALLDIR)	
	@$(MKDIR) $(INSTALLDIR)/lib
	@$(MKDIR) $(INSTALLDIR)/include	
	@$(RM) -r $(INSTALLDIR)/include/$(PROG) 
	@$(MKDIR) $(INSTALLDIR)/include/$(PROG) 
	@$(CP) $(LIBDIR)/$(REALNAME) $(INSTALLDIR)/lib
	@$(CP) $(INCDIR)/$(PROG)/*.hpp $(INSTALLDIR)/include/$(PROG)
	@$(RM) $(INSTALLDIR)/lib/$(SONAME)
	@$(RM) $(INSTALLDIR)/lib/$(LIBNAME)
	@$(CD) $(INSTALLDIR)/lib; $(LN) $(REALNAME) $(SONAME)
	@$(CD) $(INSTALLDIR)/lib; $(LN) $(SONAME) $(LIBNAME)

dist : version versioncheck
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

versioncheck : 
	@if [ $$(grep $(VERSION) $(CHANGES) | wc -l) -eq 0 ]; then echo "Version $(VERSION) not found in $(CHANGES)!"; exit 1; fi  

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
	@if [ ! -f $(PROGVER)/local/lib/$(REALNAME) ]; then exit 1; fi
	@if [ ! -f $(PROGVER)/local/lib/$(SONAME) ]; then exit 1; fi
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

upload : dist
	@$(ECHO) "Uploading version "$(VERSION)
	@./upload.sh $(VERSION) || exit 1
 
clean :
	@$(ECHO) "Cleaning up ..."
	@$(RM) -r $(LIBDIR)
	@$(RM) src/*.o
	@for dir in $(BUILDDIRS); do $(MAKE) -s -C $$dir $@ ; done
