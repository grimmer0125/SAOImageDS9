#!/bin/bash -norc
dnl	This file is an input file used by the GNU "autoconf" program to
dnl	generate the file "configure", which is run during Tcl installation
dnl	to configure the system for the local environment.

#-----------------------------------------------------------------------
# Sample configure.in for Tcl Extensions.  The only places you should
# need to modify this file are marked by the string __CHANGE__
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# __CHANGE__
# Set your package name and version numbers here.
#
# This initializes the environment with PACKAGE_NAME and PACKAGE_VERSION
# set as provided.  These will also be added as -D defs in your Makefile
# so you can encode the package version directly into the source files.
# This will also define a special symbol for Windows (BUILD_<PACKAGE_NAME>
# so that we create the export library with the dll.
#-----------------------------------------------------------------------

AC_INIT([saods9], [7.6])

#--------------------------------------------------------------------
# Call TEA_INIT as the first TEA_ macro to set up initial vars.
# This will define a ${TEA_PLATFORM} variable == "unix" or "windows"
# as well as PKG_LIB_FILE and PKG_STUB_LIB_FILE.
#--------------------------------------------------------------------

TEA_INIT([3.10])

AC_CONFIG_AUX_DIR(../tclconfig)

#--------------------------------------------------------------------

AC_ARG_WITH([arch],AC_HELP_STRING([--with-arch],[build name]),[],[with_arch=unknown])

OS="macosx"
AC_SUBST(OS)

ARCH=$with_arch
AC_SUBST(ARCH)

prefix=$ac_pwd
exec_prefix=$ac_pwd

CORES=`sysctl -n "hw.ncpu"`
AC_SUBST(CORES)

AC_OUTPUT([Makefile])

