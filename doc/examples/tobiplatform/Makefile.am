AM_CPPFLAGS = -I$(top_srcdir)/src

check_PROGRAMS = tptcpclient \
				 tptcpserver \
				 tpicclient \
				 tpicserver \
				 tpidclient

tptcpclient_SOURCES = tptcpclient.cpp
tptcpserver_SOURCES = tptcpserver.cpp
tpicclient_SOURCES = tpicclient.cpp
tpicserver_SOURCES = tpicserver.cpp
tpidclient_SOURCES = tpidclient.cpp

LDADD = $(top_builddir)/src/tobiplatform/libtobiplatform.la \
		$(top_builddir)/src/tobicore/libtobicore.la \
		$(top_builddir)/src/tobiic/libtobiic.la \
		$(top_builddir)/src/tobiid/libtobiid.la
