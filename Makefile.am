ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = doc
dist-hook:
	make clean -C $(top_distdir)/doc/doxygen

SUBDIRS = \
src/lib \
test \
examples

TESTS = \
test/unittest \
examples/collection/collection \
examples/explicit/explicit \
examples/minimal/minimal \
examples/random/random \
examples/templates/templates
