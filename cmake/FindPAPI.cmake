# Output variables:
#  PAPI_LIBRARY           : Library path of libpapi.a/libpapi.so
#  PAPI_INCLUDE_DIR       : Include directory for PAPI headers
#  PAPI_STATIC_FOUND      : True if libpapi.a found.
#  PAPI_DYNAMIC_FOUND     : True if libpapi.so found.

SET(PAPI_STATIC_FOUND FALSE)
SET(PAPI_DYNAMIC_FOUND FALSE)

IF(PAPI_ROOT)
  FIND_LIBRARY(PAPI_STATIC_LIBRARY libpapi.a
    HINTS
    ${PAPI_ROOT}
    ${PAPI_ROOT}/src
    )
  FIND_LIBRARY(PAPI_DYNAMIC_LIBRARY libpapi.so
    HINTS
    ${PAPI_ROOT}
    ${PAPI_ROOT}/src
    )
  FIND_FILE(PAPI_H "papi.h"
    HINTS
    ${PAPI_ROOT}
    ${PAPI_ROOT}/src
    )
ELSE(!PAPI_ROOT)
  FIND_LIBRARY(PAPI_STATIC_LIBRARY libpapi.a)
  FIND_LIBRARY(PAPI_DYNAMIC_LIBRARY libpapi.so)
  FIND_FILE(PAPI_H "papi.h")
ENDIF(PAPI_ROOT)

IF (PAPI_H AND PAPI_STATIC_LIBRARY)
  SET(PAPI_STATIC_FOUND TRUE)
  STRING(REPLACE "papi.h" "" PAPI_INCLUDE_DIR ${PAPI_H})
  SET(PAPI_LIBRARY ${PAPI_STATIC_LIBRARY})
  MESSAGE(STATUS "Found papi: inc=${PAPI_INCLUDE_DIR}, lib=${PAPI_LIBRARY}")
ELSEIF(PAPI_H AND PAPI_DYNAMIC_LIBRARY)
  SET(PAPI_DYNAMIC_FOUND TRUE)
  STRING(REPLACE "papi.h" "" PAPI_INCLUDE_DIR ${PAPI_H})
  SET(PAPI_LIBRARY ${PAPI_DYNAMIC_LIBRARY})
  MESSAGE(STATUS "Found papi: inc=${PAPI_INCLUDE_DIR}, lib=${PAPI_LIBRARY}")
ENDIF()
