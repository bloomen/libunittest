COMMONFLAGS = -g -O0 -Wall -Wextra -Weffc++ -pedantic -std=c++0x
ifeq ($(shell uname), Darwin)
    CXX = clang++
    CXXFLAGS = $(COMMONFLAGS) -arch x86_64 -stdlib=libc++
else
    CXX = g++
    CXXFLAGS = $(COMMONFLAGS) -pthread -fPIC -fmessage-length=0 -D_GLIBCXX_USE_NANOSLEEP
endif
LD = $(CXX)

ROOT = .
INCDIR = $(ROOT)/include
LIBDIR = $(ROOT)/lib
XSD = $(ROOT)/doc/web/libunittest.xsd

RM = rm -f

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@
