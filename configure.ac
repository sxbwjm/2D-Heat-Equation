#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([final project], [0.01])
AM_INIT_AUTOMAKE([-Wall foreign])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Checks for programs.
AC_PROG_CC([openmpicc mpicc])
AC_PROG_CC_C99
if test -z "$CC" || test "X$CC" = "Xno"; then
  AC_MSG_ERROR([No suitable C99 compiler found])
fi
AM_PROG_CC_C_O

AC_PROG_RANLIB

# Check for debugging 
AC_ARG_ENABLE(debug, 
  AS_HELP_STRING([--disable-debug], [Turn off debugging]), 
  [case "${enableval}" in 
     yes) debug=true ;; 
     no)  debug=false ;; 
     *) AC_MSG_ERROR(bad value ${enableval} for --enable-debug) ;; 
   esac], 
  [debug=true]) 
 
AS_IF([test "x$debug" = xfalse], [CPPFLAGS="${CPPFLAGS} -DNDEBUG"]) 

AC_PROG_FC([openmpif90 mpif90])
if test -z "$FC" || test "X$FC" = "Xno"; then
 AC_MSG_ERROR([No suitable FC compiler found])
fi

m4_ifdef([AM_PROG_AR], [AM_PROG_AR])

# create directory for output
AC_CONFIG_COMMANDS([mkdir], [$MKDIR_P output])

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

echo ""
echo "                       Configure Summary"
echo "                       ================="
echo ""
echo "Compiling Options:"
echo "------------------"
echo "                     C Compiler: $CC"
echo "                       CPPFLAGS: $CPPFLAGS"
echo "                         CFLAGS: $CFLAGS"
echo "                    FC Compiler: $FC"
echo "                        FCFLAGS: $FFLAGS"
echo "                        LDFLAGS: $LDFLAGS"
echo "                           LIBS: $LIBS"


