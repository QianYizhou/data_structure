#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
#AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_INIT([CPPUTEST_LCOV_AUTOTOOL_TEMPLATE], [v1.0], [qianyizhou@siasun.com])
#AC_CONFIG_SRCDIR([project/common/rsp.h])
AC_CONFIG_SRCDIR([include/CppUTest/])
AC_CONFIG_SRCDIR([include/CppUTestExt/])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX

# Enable libtools
AC_PROG_LIBTOOL

# Checks for libraries.
AC_PROG_RANLIB

#AC_CHECK_LIB([rsp_alarm], [main])
## FIXME: Replace `main' with a function in `-lrsp_dev':
#AC_CHECK_LIB([rsp_dev], [main])
## FIXME: Replace `main' with a function in `-lrsp_log':
#AC_CHECK_LIB([rsp_log], [main])
## FIXME: Replace `main' with a function in `-lrsp_memOp':
#AC_CHECK_LIB([rsp_memOp], [main])
## FIXME: Replace `main' with a function in `-lrsp_timer':
#AC_CHECK_LIB([rsp_timer], [main])
## FIXME: Replace `main' with a function in `-lrt':
#AC_CHECK_LIB([rt], [main])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h stdlib.h string.h strings.h sys/ioctl.h sys/socket.h termios.h unistd.h])

# Args for BoardType Info. Type: LX800 / E600
# QianYizhou Add
AC_ARG_WITH([boardtype],
            AC_HELP_STRING(
                           [--with-boardtype=Type],
                           [set boardtype (type: LX800/E600/E3845. default to E600)]
            ),
            [
                _boardtype=[$withval]
            ],
            [
                _boardtype="E600"
            ]
)

if test "x${_boardtype}" = "xLX800"; then
    BD_TYPE="BD_TYPE_LX800"
    LX800_STATE=true
else
    LX800_STATE=false
fi

if test "x${_boardtype}" = "xE600"; then
    BD_TYPE="BD_TYPE_E600"
    E600_STATE=true
else
    E600_STATE=false
fi

if test "x${_boardtype}" = "xE3845"; then
    BD_TYPE="BD_TYPE_E3845"
    E3845_STATE=true
else
    E3845_STATE=false
fi

AC_SUBST(BOARD_TYPE,[$BD_TYPE])
AM_CONDITIONAL(LX800_ENA, test x$LX800_STATE = xtrue)
AM_CONDITIONAL(E600_ENA, test x$E600_STATE = xtrue)
AM_CONDITIONAL(E3845_ENA, test x$E3845_STATE = xtrue) 
#AC_SUBST(LX800_ENA,[$LX800_STATE])
#AC_SUBST(E600_ENA,[$E600_STATE])

#AC_DEFINE([UART_DEV_NAME],["${uart_dev}"],[what use?])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([bzero memset mkdir munmap socket])

AC_CONFIG_FILES([Makefile \
                 build/Makefile])
AC_OUTPUT
