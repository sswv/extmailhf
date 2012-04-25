plugindir = $(CLAWS_MAIL_PLUGINDIR)

plugin_LTLIBRARIES = extmailhf_plugin.la

extmailhf_plugin_la_SOURCES = \
	extmailhf_plugin.c

extmailhf_plugin_la_LDFLAGS = \
	-avoid-version -module \
	$(GTK_LIBS)

AM_CPPFLAGS = \
	$(CLAWS_MAIL_CFLAGS) \
	$(GLIB_CFLAGS) \
	$(GTK_CFLAGS)

EXTRA_DIST=
