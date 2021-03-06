AC_INIT(src/extmailhf_plugin.c)
AC_CONFIG_AUX_DIR(config)
AM_MAINTAINER_MODE

PACKAGE=extmailhf-plugin

dnl plugin version
MAJOR_VERSION=0
MINOR_VERSION=5
MICRO_VERSION=0
EXTRA_VERSION=0

if test \( $EXTRA_VERSION -eq 0 \); then
    if test \( $MICRO_VERSION -eq 0 \); then
        VERSION=${MAJOR_VERSION}.${MINOR_VERSION} 
    else
		VERSION=${MAJOR_VERSION}.${MINOR_VERSION}.${MICRO_VERSION}
    fi
else
    if test \( $MICRO_VERSION -eq 0 \); then
        VERSION=${MAJOR_VERSION}.${MINOR_VERSION}cvs${EXTRA_VERSION}
    else
		VERSION=${MAJOR_VERSION}.${MINOR_VERSION}.${MICRO_VERSION}cvs${EXTRA_VERSION}
    fi
fi

AM_INIT_AUTOMAKE($PACKAGE, $VERSION, no-define)
AM_CONFIG_HEADER(pluginconfig.h)
AC_DEFINE_UNQUOTED(PLUGINVERSION, "$VERSION", [plugin version])

AC_PROG_CC
AC_ISC_POSIX
AM_PROG_CC_STDC
AC_PROG_INSTALL
AC_PROG_CPP
AM_PROG_LIBTOOL
AC_SYS_LARGEFILE


AC_MSG_CHECKING([if gcc supports -Wno-pointer-sign])
_gcc_cflags_save=$CFLAGS
CFLAGS="-Wno-pointer-sign"
AC_COMPILE_IFELSE(AC_LANG_PROGRAM([]),_gcc_psign=yes,_gcc_psign=no)
AC_MSG_RESULT($_gcc_psign)
CFLAGS=$_gcc_cflags_save;
if test x"$_gcc_psign" = xyes ; then
	CFLAGS="$CFLAGS -Wno-pointer-sign"
fi

CFLAGS="$CFLAGS -Wall"
if test $USE_MAINTAINER_MODE = yes; then
	CFLAGS="$CFLAGS -DGTK_DISABLE_DEPRECATED -DGDK_DISABLE_DEPRECATED -DG_DISABLE_DEPRECATED"
fi

#
# Find pkg-config
#
AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
if test x$PKG_CONFIG = xno ; then
  AC_MSG_ERROR([*** pkg-config not found. See http://www.freedesktop.org/software/pkgconfig/])
fi

#
# Check for claws-mail
#
PKG_CHECK_MODULES(CLAWS_MAIL, claws-mail >= 3.1.0.0)
if test -z $prefix || test "${prefix}" = "NONE" ; then
  prefix=$( $PKG_CONFIG --variable=prefix claws-mail )
  CLAWS_MAIL_PLUGINDIR=$( $PKG_CONFIG --variable=plugindir claws-mail )
else
  CLAWS_MAIL_PLUGINDIR='${libdir}/claws-mail/plugins'
fi
AC_SUBST(CLAWS_MAIL_CFLAGS)
AC_SUBST(CLAWS_MAIL_LIBS)
AC_SUBST(CLAWS_MAIL_PLUGINDIR)

dnl Check for GLib
PKG_CHECK_MODULES(GLIB, glib-2.0 >= 2.6 gmodule-2.0 >= 2.6 gobject-2.0 >= 2.6 gthread-2.0 >= 2.6)
      
GLIB_GENMARSHAL=`pkg-config --variable=glib_genmarshal glib-2.0`
AC_SUBST(GLIB_GENMARSHAL)

AC_SUBST(GLIB_CFLAGS)
AC_SUBST(GLIB_LIBS)

dnl Check for GTK+
PKG_CHECK_MODULES(GTK, gtk+-2.0 >= 2.6)

AC_SUBST(VERSION)
AC_SUBST(PLUGINVERSION)
AC_SUBST(MAJOR_VERSION)
AC_SUBST(MINOR_VERSION)
AC_SUBST(MICRO_VERSION)
AC_SUBST(EXTRA_VERSION)

AC_OUTPUT([
Makefile
src/Makefile
])
