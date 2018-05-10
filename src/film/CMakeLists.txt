set(FILM_SRCS
    ${CMAKE_SOURCE_DIR}/include/Gregar_v.01)

set(C_SRCS
    film.cpp
    ldrfilm.cpp)

SET(LIB_TYPE STATIC)

add_library(film ${LIB_TYPE} ${FILM_SRCS} ${C_SRCS})

add_executable(FILM_TESTER unit_test_film.cpp)