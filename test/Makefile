PROG = unittest.exe

INCDIR = ../include
LIBDIR = ../lib
XSD = ../doc/web/libunittest.xsd

ifeq ($(shell uname), Darwin)
    CXX = clang++
    CXXFLAGS = -arch x86_64 -g -O0 -Wall -pedantic -std=c++0x -stdlib=libc++
    LDFLAGS =
else
    CXX = g++
    CXXFLAGS = -g -O0 -Wall -pedantic -std=c++0x -pthread -fPIC -fmessage-length=0 -D_GLIBCXX_USE_NANOSLEEP
    LDFLAGS = -pthread
endif
LD = $(CXX)

INCS = -I./$(INCDIR) 
LIBS = ./$(LIBDIR)/libunittest.so
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

RM = rm -f

default : $(PROG)
all : default

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@

$(PROG) : $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(PROG)

run :
	@export LD_LIBRARY_PATH=$(LIBDIR):$(LD_LIBRARY_PATH); export DYLD_LIBRARY_PATH=$(LIBDIR):$(DYLD_LIBRARY_PATH); export PATH=$(LIBDIR):$(PATH); ./$(PROG) -x || exit 1
	@xmllint --noout --schema $(XSD) libunittest.xml || exit 1

clean :
	$(RM) $(PROG) *.o *.xml
