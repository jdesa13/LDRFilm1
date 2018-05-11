

set(FILM_SRCS
    ${GREGAR_INCLUDE_DIR}/Gregar_v.01/film.h film.cpp
    ${GREGAR_INCLUDE_DIR}/Gregar_v.01/ldrfilm.h ldrfilm.cpp)

set(STB_INCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/external_libraries/stb)

SET(LIB_TYPE STATIC)

include_directories(${STB_INCLUDE_DIR} ${GREGAR_INCLUDE_DIR})

add_library(film ${LIB_TYPE} ${FILM_SRCS})


add_executable(FILM_TESTER unit_test_film.cpp)

target_link_libraries(FILM_TESTER film core)
ADD_DEPENDENCIES(FILM_TESTER film)