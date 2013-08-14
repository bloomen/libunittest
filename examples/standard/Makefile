PROG = unittest

INCDIR = ../../include
LIBDIR = ../../lib

UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
CXX = clang++ -stdlib=libc++ -U__STRICT_ANSI__
DYLD_LIBRARY_PATH := $(DYLD_LIBRARY_PATH):$(LIBDIR)
SUFFIX = 
else
CXX = g++
UNAMECUT = $(shell echo $(UNAME) | head -c6)
ifeq ($(UNAMECUT), CYGWIN)
PATH := $(LIBDIR):$(PATH)
SUFFIX = .exe
else
LD_LIBRARY_PATH := $(LIBDIR):$(LD_LIBRARY_PATH)
SUFFIX = 
endif
endif

CXXFLAGS = -O0 -g3 -Wall -std=c++0x -pthread
LDFLAGS = -pthread

INCS = -I"$(INCDIR)" 
LIBS = -L"$(LIBDIR)" -lunittest
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

RM = rm -f

default : $(PROG)
all : default

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I./$(INCDIR) -c $< -o $@

$(PROG) : $(OBJECTS)
	@$(MAKE) -s -C .. version
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(PROG)

run :
	@./$(PROG)$(SUFFIX) $(ARGS) || exit 1

clean :
	$(RM) $(PROG) $(OBJECTS)
