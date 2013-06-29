VERSION = $(shell head -n 1 ../VERSION.txt)

SED = sed
SEDFLAGS = -e "s/LIBUNITTEST_VERSION/$(VERSION)/g"

DOXYGEN = doxygen
TEMPLATE_DOXYFILE = template_doxyfile
DOXYFILE = doxyfile

ECHO = echo
RM = rm -rf

all :
	@$(ECHO) "Running doxygen for libunittest-$(VERSION) ..."
	@$(SED) $(SEDFLAGS) $(TEMPLATE_DOXYFILE) > $(DOXYFILE)
	@$(DOXYGEN) >/dev/null

clean :
	$(RM) $(DOXYFILE) html/
