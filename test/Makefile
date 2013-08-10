PROG = unittest

UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
CXX = clang++ -stdlib=libc++ -U__STRICT_ANSI__
else
CXX = g++
endif

FLAGS = -O0 -g3 -Wall -std=c++0x -pthread

INCDIR = ../include
LIBDIR = ../lib

INCS = -I"$(INCDIR)" 
LIBS = -L"$(LIBDIR)" -lunittest
SRCS = *.cpp

CHMOD = chmod
RM = rm -f

all :
	$(CXX) $(FLAGS) $(INCS) $(SRCS) $(LIBS) -o $(PROG)

run :
	@LD_LIBRARY_PATH=$(LIBDIR):$(LD_LIBRARY_PATH) \
	 DYLD_LIBRARY_PATH=$(LIBDIR):$(DYLD_LIBRARY_PATH) \
	 ./$(PROG) $(ARGS) || exit 1

clean :
	$(RM) $(PROG)
	