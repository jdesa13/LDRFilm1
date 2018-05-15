

set(FILM_SRCS
    ${GREGAR_INCLUDE_DIR}/Gregar_v.01/film.h film.cpp
    ${GREGAR_INCLUDE_DIR}/Gregar_v.01/ldrfilm.h ldrfilm.cpp
    ${GREGAR_INCLUDE_DIR}/Gregar_v.01/numfilm.h numfilm.cpp)

set(STB_INCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/external_libraries/stb)

set(CNPY_INCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/external_libraries/cnpy)

set(ZLIB_INCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/external_libraries/zlib)

SET(LIB_TYPE STATIC)

include_directories(${STB_INCLUDE_DIR} ${GREGAR_INCLUDE_DIR} ${CNPY_INCLUDE_DIR} ${ZLIB_INCLUDE_DIR})

add_library(film ${LIB_TYPE} ${FILM_SRCS})


add_executable(FILM_TESTER unit_test_film.cpp)

target_link_libraries(FILM_TESTER film core)
ADD_DEPENDENCIES(FILM_TESTER film)