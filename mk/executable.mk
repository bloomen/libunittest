PROG = unittest.exe

ifeq ($(shell uname), Darwin)
    LDFLAGS =
else
    LDFLAGS = -pthread
endif

INCS = -I$(INCDIR) 
LIBS = -L./$(LIBDIR) -lunittest
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

default : $(PROG)
all : default

$(PROG) : $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(PROG)

run :
	@export LD_LIBRARY_PATH=$(LIBDIR):$(LD_LIBRARY_PATH); export DYLD_LIBRARY_PATH=$(LIBDIR):$(DYLD_LIBRARY_PATH); export PATH=$(LIBDIR):$(PATH); ./$(PROG) -x || exit 1
	@xmllint --noout --schema $(XSD) libunittest.xml || exit 1

clean :
	$(RM) $(PROG) *.o *.xml
