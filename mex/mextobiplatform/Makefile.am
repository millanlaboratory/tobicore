interface = tobiplatform
mexcc = $(interface).cc
mexmw = $(top_srcdir)/mex/mex$(interface)/$(interface).mw
mexld = -L$(abs_top_builddir)/src/$(interface)/.libs/ -l$(interface) \
		-L$(abs_top_builddir)/src/tobicore/.libs/ -ltobicore \
		-L$(abs_top_builddir)/src/tobiic/.libs/ -ltobiic \
		-L$(abs_top_builddir)/src/tobiid/.libs/ -ltobiid
mexinc = -I$(top_srcdir)/src/
mexpath = ${DESTDIR}${pkgdatadir}/tobicoremat/mex$(interface)/
if WIN32
mexwin = $(top_srcdir)/mex/mex$(interface)/make.m
verwin = win32-$(CURRENT).$(REVISION).$(AGE)
tarwin = mex$(interface)-$(verwin).tar.bz2
docwin = $(top_srcdir)/doc/examples/mex$(interface)
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
