set (CORE_SRCS
     ${CMAKE_SOURCE_DIR}/include/Gregar_v.01)

SET(LIB_TYPE STATIC)

add_library(core ${LIB_TYPE} ${CORE_SRCS})