VERSION = $(shell bash version.sh)

SED = sed -e "s/LIBUNITTEST_VERSION/$(VERSION)/g"

DOXYGEN = doxygen
TEMPLATE = template_doxyfile
DOXYFILE = doxyfile

ECHO = echo
RM = rm -rf

all :
	@$(ECHO) "Running doxygen for libunittest-$(VERSION) ..."
	@$(SED) $(TEMPLATE) > $(DOXYFILE)
	@$(DOXYGEN) >/dev/null

clean :
	$(RM) $(DOXYFILE) html/
