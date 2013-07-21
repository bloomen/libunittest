VERSION = $(shell bash version.sh)

SED = sed -e "s/LIBUNITTEST_VERSION/$(VERSION)/g"

DOXYGEN = doxygen
TEMPLATE = template_doxyfile
DOXYFILE = doxyfile
ERRLOG = errors.log

ECHO = echo
RM = rm -rf

all :
	@$(RM) $(ERRLOG)
	@$(ECHO) "Running doxygen for libunittest-$(VERSION) ..."
	@$(SED) $(TEMPLATE) > $(DOXYFILE)
	@$(DOXYGEN) >/dev/null 2>$(ERRLOG)
	@if [ -s $(ERRLOG) ]; then cat $(ERRLOG); exit 1; fi 
	@$(RM) $(ERRLOG)
	@$(ECHO) "Entry point: html/index.html"

clean :
	$(RM) $(ERRLOG) $(DOXYFILE) html/
