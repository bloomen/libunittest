# initial information about the project
AC_INIT([libunittest],[8.0.0],[chr.blume@gmail.com])

# check if the source folder is available
AC_CONFIG_SRCDIR([src/main.cpp])

AC_CONFIG_HEADERS([src/config.hpp])

AC_CONFIG_MACRO_DIR([m4])

# automake initialization (mandatory) including a check for automake API version >= 1.9
AM_INIT_AUTOMAKE([1.9])

LT_INIT

# check for C++ preprocessor and compiler
AC_PROG_CXX

# use the C++ compiler for the following checks
AC_LANG([C++])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([string])
AC_CHECK_HEADERS([iostream])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])

# distribute additional compiler and linker flags among Makefiles
# --> set and change these variables instead of CXXFLAGS or LDFLAGS (for user only)
#AC_SUBST([AM_CXXFLAGS])
#AC_SUBST([AM_LDFLAGS])
#AC_SUBST([LIBS])

# files to generate via autotools (prepare .am or .in source files)
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([src/Makefile])

AC_PROG_INSTALL

# finally this generates the Makefiles etc. for the build
AC_OUTPUT
