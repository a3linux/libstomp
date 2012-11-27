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
PKG_CHECK_MODULES([APR],[apr-1])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([strstr])


AC_CONFIG_FILES([Makefile
		src/Makefile])
AC_OUTPUT
