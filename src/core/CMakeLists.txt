set (CORE_SRCS
     create.h create.cpp)

SET(LIB_TYPE STATIC)

add_library(core ${LIB_TYPE} ${CORE_SRCS})