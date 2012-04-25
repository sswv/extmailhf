/*
 * Program: ExtmailHeaderFixer - Plugin for Claws Mail
 * Author:  Jian Lin <lj [at] linjian.org>
 * License: GPL (See file COPYING)
 * Depends: Claws Mail
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "defs.h"

#include <glib.h>
#include <glib/gi18n.h>

#include "version.h"
#include "claws.h"
#include "plugin.h"
#include "utils.h"
#include "hooks.h"
#include "prefs.h"
#include "prefs_gtk.h"
#include "pop.h"
#include "pluginconfig.h"

static guint mail_receive_hook_id;

static gboolean mail_receive_hook(gpointer source, gpointer data)
{
	MailReceiveData *mail_receive_data = (MailReceiveData *)source;

	gchar *foundend = NULL;
	gchar *foundext = NULL;
	gchar *foundmix = NULL;
	gchar *foundb64 = NULL;
	gssize headlen = 0;

	debug_print("$$$ ExtmailHeaderFixer start.\n");

	g_return_val_if_fail( 
		mail_receive_data
		&& mail_receive_data->session
		&& mail_receive_data->data,
		FALSE);

	(foundend = g_strstr_len(mail_receive_data->data, -1, "\r\n\r\n")) != NULL || 
	(foundend = g_strstr_len(mail_receive_data->data, -1, "\n\n")) != NULL || 
	(foundend = g_strstr_len(mail_receive_data->data, -1, "\r\r")) != NULL;

	headlen = foundend - mail_receive_data->data;

	debug_print("$$$ mail_receive_data->data=%ld, foundend=%ld, headlen=%ld.\n", mail_receive_data->data, foundend, headlen);

	if (foundend == NULL || headlen < 0) {
		return FALSE;
	}

	(foundext = g_strstr_len(mail_receive_data->data, headlen, "X-Mailer: ExtMail")) != NULL && 
	(foundmix = g_strstr_len(mail_receive_data->data, headlen, "Content-Type: multipart/mixed")) != NULL &&
	(foundb64 = g_strstr_len(mail_receive_data->data, headlen, "Content-Transfer-Encoding: base64")) != NULL;

	debug_print("$$$ foundext=%ld, foundmix=%ld, foundb64=%ld.\n", foundext, foundmix, foundb64);

	if (foundb64 != NULL) {
		strncpy(foundb64, "X-Extmail-Header-Encoding", sizeof("X-Extmail-Header-Encoding") - 1);
		debug_print("$$$ fixing Extmail header.\n");
	}

	debug_print("$$$ ExtmailHeaderFixer end.\n");

	return FALSE;
}

gint plugin_init(gchar **error)
{
	if (!check_plugin_version(MAKE_NUMERIC_VERSION(2,9,2,72),
		VERSION_NUMERIC, _("ExtmailHeaderFixer"), error))
		return -1;

	mail_receive_hook_id = hooks_register_hook(MAIL_RECEIVE_HOOKLIST, mail_receive_hook, NULL);
	if (mail_receive_hook_id == (guint)-1) {
		*error = g_strdup("Failed to register mail receive hook");
		return -1;
	}

	debug_print("ExtmailHeaderFixer plugin loaded\n");

	return 0;
}

gboolean plugin_done(void)
{
	hooks_unregister_hook(MAIL_RECEIVE_HOOKLIST, mail_receive_hook_id);

	debug_print("ExtmailHeaderFixer plugin unloaded\n");
	return TRUE;
}

const gchar *plugin_name(void)
{
	return _("ExtmailHeaderFixer");
}

const gchar *plugin_desc(void)
{
	return _("This plugin modifies the messages from Extmail whose header violating RFC 2046. "
		"See http://blog.linjian.org/articles/extmail-multipart-bug/ for details.\n");
}

const gchar *plugin_type(void)
{
	return "GTK2";
}

const gchar *plugin_licence(void)
{
		return "GPL3+";
}

const gchar *plugin_version(void)
{
	return PLUGINVERSION;
}

struct PluginFeature *plugin_provides(void)
{
	static struct PluginFeature features[] = 
		{{PLUGIN_UTILITY, N_("Extmail header fixing")},
		{PLUGIN_NOTHING, NULL}};
	return features;
}
