#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([libstomp], 0.1.0, a3linux@gmail.com)
AM_INIT_AUTOMAKE(libstomp, 0.1.0)
AC_PROG_LIBTOOL

AC_CONFIG_SRCDIR([src/stomp.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

AC_CHECK_LIB([apr-1],[apr_socket_create],[HAVE_APR=yes],[HAVE_APR=no])
if test "$HAVE_APR" = "no"; then
	AC_MSG_ERROR([apr is required])
fi

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])
AC_CHECK_HEADER([apr-1/apr.h], [], [], 
[[#ifdef HAVE_APR_1_APR_H
 #include <apr-1/apr.h>
 #endif
 ]])
# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([strstr])


AC_CONFIG_FILES([
				Makefile
				src/Makefile
				])
AC_OUTPUT
