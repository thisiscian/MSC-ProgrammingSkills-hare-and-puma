AC_INIT([hare-and-puma], [0.1], [this.is.cian@gmail.com])

AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

#programs used
AC_PROG_LIBTOOL
AC_PROG_CC
AC_PROG_CXX

#require boost installed
BOOST_REQUIRE
BOOST_PROGRAM_OPTIONS

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])

AC_OUTPUT
