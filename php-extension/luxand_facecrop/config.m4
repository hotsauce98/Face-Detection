PHP_ARG_WITH(luxand_facecrop, for luxand_facecrop support, [  --with-luxand_facecrop[=/path/to/facecrop/library]     Enable luxand_facecrop support])

if test "$PHP_LUXAND_FACECROP" != "no"; then
  PHP_REQUIRE_CXX
  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR_H="include/LuxandFaceCrop.h"
  SEARCH_FOR_LIB="lib/libfacecrop"

  if test -r $PHP_LUXAND_FACECROP/$SEARCH_FOR_H && test -r $PHP_LUXAND_FACECROP/$SEARCH_FOR_LIB.$SHLIB_SUFFIX_NAME; then
    LUXAND_FACECROP_DIR=$PHP_LUXAND_FACECROP
  else
    AC_MSG_CHECKING([for LuxandFaceCrop.h and libfacecrop.$SHLIB_SUFFIX_NAME in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR_H && test -r $i/$SEARCH_FOR_LIB.$SHLIB_SUFFIX_NAME; then
        LUXAND_FACECROP_DIR=$i
        AC_MSG_RESULT(found in $i)
        break
      fi
    done
  fi

  if test -z "$LUXAND_FACECROP_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please place libfacecrop.$SHLIB_SUFFIX_NAME file to /usr/lib or /usr/local/lib and LuxandFaceCrop.h file to /usr/include or /usr/local/include])
  fi

  PHP_ADD_INCLUDE($LUXAND_FACECROP_DIR/include)

  AC_LANG_PUSH(C++)
  AC_CHECK_HEADER([LuxandFaceCrop.h], [], AC_MSG_ERROR('LuxandFaceCrop.h' header not found))

  PHP_ADD_LIBRARY_WITH_PATH(stdc++, "", LUXAND_FACECROP_SHARED_LIBADD)

  PHP_ADD_LIBRARY_WITH_PATH(facecrop, $LUXAND_FACECROP_DIR/lib, LUXAND_FACECROP_SHARED_LIBADD)
  AC_LANG_POP(C++)

  PHP_SUBST(LUXAND_FACECROP_SHARED_LIBADD)
  AC_DEFINE(HAVE_LUXAND_FACECROP, 1, [ ])
  PHP_NEW_EXTENSION(luxand_facecrop, luxand_facecrop.cpp, $ext_shared)
fi

