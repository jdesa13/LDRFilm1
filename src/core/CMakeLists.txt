set (CORE_SRCS
     corefilm.h corefilm.cpp)

SET(LIB_TYPE STATIC)

add_library(core ${LIB_TYPE} ${CORE_SRCS})