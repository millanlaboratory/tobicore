interface = tobicore
mexcc = $(interface).cc
mexmw = $(top_srcdir)/mex/mex$(interface)/$(interface).mw
mexld = -L$(abs_top_builddir)/src/$(interface)/.libs/ -l$(interface)
mexinc = -I$(top_srcdir)/src/
mexpath = ${DESTDIR}${pkgdatadir}/tobicoremat/mex$(interface)/
if WIN32
mexwin = $(top_srcdir)/mex/mex$(interface)/make.m
verwin = win32-$(CURRENT).$(REVISION).$(AGE)
tarwin = mex$(interface)-$(verwin).tar.bz2
docwin = $(top_srcdir)/doc/examples/mex$(interface)
# Hack for building DLL distribution
dirdll = $(interface)-$(verwin)
tardll = $(interface)-$(verwin).tar.bz2
endif

EXTRA_DIST = ${mexmw}

all: mex

$(interface).cc: $(mexmw)
	mwrap -mex $(interface) -c $(mexcc) -mb $(mexmw) 

mex: $(interface).cc
if LINUX
	mex -largeArrayDims $(mexinc) $(mexcc) $(mexld)
else
	cp $(mexwin) .
	matlab -nodesktop -wait -r make
	rm make.m
	tar -cjf $(top_builddir)/$(tarwin) $(docwin) *.m *.mex*
	@echo "Creating DLL tarball in the dirtiest possible way"
	mkdir -p $(top_builddir)/$(dirdll)
	find $(top_builddir)/src/ -iname *.dll | xargs -i cp {} $(top_builddir)/$(dirdll)/
	tar -cjf $(top_builddir)/$(tardll) $(top_builddir)/$(dirdll)/*.dll
endif

clean-local:
	rm -rf $(mexcc)
	rm -rf *.m
	rm -rf *.mex*

install-data-local:
	mkdir -p ${mexpath}
	cp *.m ${mexpath}
	cp *.mex* ${mexpath}

uninstall-local:
	rm -rf ${mexpath}
