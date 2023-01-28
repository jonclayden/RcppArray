AC_PREREQ([2.71])
AC_INIT([span.test], [0.1], [code@clayden.org])

CXX20=`"${R_HOME}/bin/R" CMD config CXX20`
if test -z "$CXX20"; then
  AC_MSG_ERROR([No C++20 compiler is available])
fi
CXX20STD=`"${R_HOME}/bin/R" CMD config CXX20STD`
CXX="${CXX20} ${CXX20STD}"
CXXFLAGS=`"${R_HOME}/bin/R" CMD config CXX20FLAGS`

AC_LANG(C++)

AC_CHECK_HEADERS([span])

AC_CONFIG_HEADERS([src/config.h])
AC_OUTPUT
