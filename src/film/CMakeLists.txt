set(FILM_SRCS
    ${CMAKE_SOURCE_DIR}/include/Gregar_v.01
)

SET(LIB_TYPE STATIC)

add_library(film ${LIB_TYPE} ${FILM_SRCS})

add_executable(FILM_TESTER unit_test_film.cpp)