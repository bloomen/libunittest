PROG = unittest.exe

INCDIR = ../include
LIBDIR = ../lib
XSD = ../doc/web/libunittest.xsd

CXX = g++
CXXFLAGS = -O0 -g3 -Wall -std=c++0x -pthread -fmessage-length=0 -D_GLIBCXX_USE_NANOSLEEP
LD = $(CXX)
LDFLAGS = -pthread 

INCS = -I$(INCDIR) 
LIBS = $(LIBDIR)/$(shell readlink -n $(LIBDIR)/libunittest.so)
LIBS := $(LIBDIR)/$(shell readlink -n $(LIBS))
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

LD_LIBRARY_PATH := $(LIBDIR):$(LD_LIBRARY_PATH)
DYLD_LIBRARY_PATH := $(LIBDIR):$(DYLD_LIBRARY_PATH)
PATH := $(LIBDIR):$(PATH)

RM = rm -f

default : $(PROG)
all : default

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I./$(INCDIR) -c $< -o $@

$(PROG) : $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(PROG)

run :
	@./$(PROG) -x $(ARGS) || exit 1
	@xmllint --noout --schema $(XSD) libunittest.xml || exit 1

clean :
	$(RM) $(PROG) *.o *.xml
