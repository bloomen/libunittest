PROG = unittest.exe

INCDIR = ../../include
LIBDIR = ../../lib
XSD = ../../doc/web/libunittest.xsd

CXX = g++
CXXFLAGS = -O0 -g3 -Wall -std=c++0x -pthread -fmessage-length=0 -D_GLIBCXX_USE_NANOSLEEP
LD = $(CXX)
LDFLAGS = -pthread 
CXXOBJ = -o
LDOBJ = -o

INCS = -I$(INCDIR) 
LIBS = $(LIBDIR)/$(shell readlink -n $(LIBDIR)/libunittest.so)
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

ifeq ($(CXX),cl)
CXXFLAGS = -GS -analyze- -W3 -Zc:wchar_t -nologo -ZI -Gm -Od -sdl -fp:precise -errorReport:none -WX- -Zc:forScope -RTC1 -Gd -Oy- -MDd -EHsc
LD = cl
LDFLAGS = -nologo -errorReport:none
CXXOBJ = -Fo:
LDOBJ = -Fe:
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
	$(LD) $(LDFLAGS) $(OBJECTS) $(LIBS) $(LDOBJ) $(PROG)

run :
	@./$(PROG) -x $(ARGS) || exit 1
	@xmllint --noout --schema $(XSD) libunittest.xml || exit 1

clean :
	$(RM) $(PROG) *.o *.xml
