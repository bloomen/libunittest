PROG = libunittest.so

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
CXX = clang++ -stdlib=libc++
else
CXX = g++
endif

FLAGS = -O2 -Wall -std=c++0x -pthread -shared -fPIC

INCS = -I"../include" 
SRCS = ../src/*.cpp

RM = rm -f

all :
	$(CXX) $(FLAGS) $(INCS) $(SRCS) -o $(PROG)

clean :
	$(RM) $(PROG)
