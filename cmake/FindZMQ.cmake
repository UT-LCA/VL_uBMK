# Output variables:
#  ZMQ_LIBRARY           : Library path of libzmq.a/libzmq.so
#  ZMQ_INCLUDE_DIR       : Include directory for zmq.h
#  ZMQ_STATIC_FOUND      : True if libzmq.a found.
#  ZMQ_DYNAMIC_FOUND     : True if libzmq.so found.

SET(ZMQ_STATIC_FOUND FALSE)
SET(ZMQ_DYNAMIC_FOUND FALSE)

IF(ZMQ_ROOT)
  FIND_LIBRARY(ZMQ_STATIC_LIBRARY libzmq.a
    HINTS
    ${ZMQ_ROOT}
    ${ZMQ_ROOT}/src/.libs
    )
  FIND_LIBRARY(ZMQ_DYNAMIC_LIBRARY libzmq.so
    HINTS
    ${ZMQ_ROOT}
    ${ZMQ_ROOT}/src/.libs
    )
  FIND_FILE(ZMQ_H "zmq.h"
    HINTS
    ${ZMQ_ROOT}/include)
ELSE(NOT ZMQ_ROOT)
  FIND_LIBRARY(ZMQ_STATIC_LIBRARY libzmq.a)
  FIND_LIBRARY(ZMQ_DYNAMIC_LIBRARY libzmq.so)
  FIND_FILE(ZMQ_H "zmq.h")
ENDIF(ZMQ_ROOT)

IF (ZMQ_H AND ZMQ_STATIC_LIBRARY)
  SET(ZMQ_STATIC_FOUND TRUE)
  STRING(REPLACE "zmq.h" "" ZMQ_INCLUDE_DIR ${ZMQ_H})
  SET(ZMQ_LIBRARY ${ZMQ_STATIC_LIBRARY})
  MESSAGE(STATUS "Found zmq: inc=${ZMQ_INCLUDE_DIR}, lib=${ZMQ_LIBRARY}")
ELSEIF(ZMQ_H AND ZMQ_DYNAMIC_LIBRARY)
  SET(ZMQ_DYNAMIC_FOUND TRUE)
  STRING(REPLACE "zmq.h" "" ZMQ_INCLUDE_DIR ${ZMQ_H})
  SET(ZMQ_LIBRARY ${ZMQ_DYNAMIC_LIBRARY})
  MESSAGE(STATUS "Found zmq: inc=${ZMQ_INCLUDE_DIR}, lib=${ZMQ_LIBRARY}")
ENDIF()
