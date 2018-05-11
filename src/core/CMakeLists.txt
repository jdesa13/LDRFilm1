set (CORE_SRCS
     ${GREGAR_INCLUDE_DIR}/Gregar_v.01/create.h create.cpp)

SET(LIB_TYPE STATIC)

include_directories(${GREGAR_INCLUDE_DIR})

add_library(core ${LIB_TYPE} ${CORE_SRCS})