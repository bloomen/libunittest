PROG = unittest.exe

ifeq ($(shell uname), Darwin)
    LDFLAGS =
else
    LDFLAGS = -pthread
endif

LIBS = -Wl,-rpath,./$(LIBDIR) -L./$(LIBDIR) -lunittest
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

default : $(PROG)
all : default

$(PROG) : $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(PROG)

run :
	@./$(PROG) -x || exit 1
	@xmllint --noout --schema $(XSD) libunittest.xml || exit 1

clean :
	$(RM) $(PROG) *.o *.xml
