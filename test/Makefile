PROG = unittest.exe

INCDIR = ../include
LIBDIR = ../lib

CXX = g++
CXXFLAGS = -O0 -g3 -Wall -std=c++0x -pthread -fmessage-length=0
LDFLAGS = -pthread 
CXXOBJ = -o
LDOBJ = -o

INCS = -I$(INCDIR) 
LIBS = $(LIBDIR)/libunittest.so
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

ifeq ($(CXX),cl)
CXXFLAGS = -GR -EHsc -W3 -nologo
LDFLAGS = -nologo
CXXOBJ = -Fo:
LDOBJ = -Fe:
LIBS = ../src/*.o
endif

LD_LIBRARY_PATH := $(LIBDIR):$(LD_LIBRARY_PATH)
DYLD_LIBRARY_PATH := $(LIBDIR):$(DYLD_LIBRARY_PATH)
PATH := $(LIBDIR):$(PATH)

RM = rm -f

default : $(PROG)
all : default

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I./$(INCDIR) -c $< $(CXXOBJ) $@

$(PROG) : $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LIBS) $(LDOBJ) $(PROG)

run :
	@./$(PROG) $(ARGS) || exit 1

clean :
	$(RM) $(PROG) *.o *.xml
