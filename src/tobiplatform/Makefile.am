AM_CPPFLAGS = $(CPPFLAGS) -I$(top_srcdir)/src
lib_LTLIBRARIES = libtobiplatform.la

libtobiplatform_includedir = $(includedir)/tobiplatform

libtobiplatform_include_HEADERS = TPSocket.hpp \
								  TPMutex.hpp \
								  TPStreamer.hpp \
								  TPInterface.hpp \
								  TPiC.hpp \
								  TPiD.hpp

libtobiplatform_la_SOURCES = TPMutex.cpp \
							 TPMutex.hpp \
							 TPStreamer.cpp \
							 TPStreamer.hpp \
							 TPSocket.cpp \
							 TPSocket.hpp \
							 TPInterface.cpp \
							 TPInterface.hpp \
							 TPiC.cpp \
							 TPiC.hpp \
							 TPiD.cpp \
							 TPiD.hpp

libtobiplatform_la_LDFLAGS = $(AM_CFLAGS) -version-info $(CURRENT):$(REVISION):$(AGE) -no-undefined
libtobiplatform_la_LIBADD = $(top_builddir)/src/tobicore/libtobicore.la \
							$(top_builddir)/src/tobiic/libtobiic.la \
							$(top_builddir)/src/tobiid/libtobiid.la \
							$(PTHREAD_LIBS) $(WIN32_LIBS)
#-lws2_32

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = tobiplatform.pc
