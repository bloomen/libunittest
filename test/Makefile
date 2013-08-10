PROG = unittest

UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
CXX = clang++ -stdlib=libc++ -U__STRICT_ANSI__
LD = clang++ -stdlib=libc++
else
CXX = g++
LD = g++
endif

CXXFLAGS = -O0 -g3 -Wall -std=c++0x -pthread
LDFLAGS = -pthread

INCDIR = ../include
LIBDIR = ../lib

INCS = -I"$(INCDIR)" 
LIBS = -L"$(LIBDIR)" -lunittest
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

RM = rm -f

default : $(PROG)
all : default

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I./$(INCDIR) -c $< -o $@

$(PROG) : $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(PROG)

run :
	@LD_LIBRARY_PATH=$(LIBDIR):$(LD_LIBRARY_PATH) \
	 DYLD_LIBRARY_PATH=$(LIBDIR):$(DYLD_LIBRARY_PATH) \
	 ./$(PROG) $(ARGS) || exit 1

clean :
	$(RM) $(PROG) $(OBJECTS)
	