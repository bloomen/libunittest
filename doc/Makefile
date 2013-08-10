DOXYGEN = doxygen
DOXYFILE = doxyfile
ERRLOG = errors.log
ENTRY = html/index.html

ECHO = echo
RM = rm -rf

all :
	@$(RM) $(ERRLOG)
	@$(ECHO) "Running doxygen ..."
	@$(DOXYGEN) >/dev/null 2>$(ERRLOG)
	@if [ -s $(ERRLOG) ]; then cat $(ERRLOG); exit 1; fi 
	@$(RM) $(ERRLOG)
	@$(ECHO) "Entry point: $(ENTRY)"

run :
	@if [ ! -f $(ENTRY) ]; then $(ECHO) "$(ENTRY) does not exist!"; exit 1; fi
	@$(ECHO) "$(ENTRY) exists"

clean :
	$(RM) $(ERRLOG) html/
