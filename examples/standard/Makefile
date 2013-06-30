PROG = unittest_example

UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
CXX = clang++ -stdlib=libc++
else
CXX = g++
endif

FLAGS = -O0 -g3 -Wall -std=c++0x -pthread

INCS = -I"../../include" 
LIBS = -L"../../build" -lunittest
SRCS = *.cpp

CHMODX = chmod u+x
RM = rm -f

all :
	$(CXX) $(FLAGS) $(INCS) $(SRCS) $(LIBS) -o $(PROG)
	$(CHMODX) run_example.sh

clean :
	$(RM) $(PROG)
