PROG = unittest.exe

INCDIR = ../../include
LIBDIR = ../../lib

CXX = g++
CXXFLAGS = -O0 -g3 -Wall -std=c++0x -pthread -fmessage-length=0
LDFLAGS = -pthread 

INCS = -I$(INCDIR) 
LIBS = $(LIBDIR)/libunittest.so
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

RM = rm -f

default : $(PROG)
all : default

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I./$(INCDIR) -c $< -o $@

$(PROG) : $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(PROG)

run :
	@./$(PROG) $(ARGS) || exit 1

clean :
	$(RM) $(PROG) *.o *.xml
