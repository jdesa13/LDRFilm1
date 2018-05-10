set(FILM_SRCS
    ${CMAKE_SOURCE_DIR}/include/Gregar_v.01/film.h film.cpp
    ${CMAKE_SOURCE_DIR}/include/Gregar_v.01/ldrfilm.h ldrfilm.cpp)

set(C_SRCS
    film.cpp
    ldrfilm.cpp)

SET(LIB_TYPE STATIC)

add_library(film ${LIB_TYPE} ${FILM_SRCS})

add_executable(FILM_TESTER unit_test_film.cpp)

#target_link_libraries(FILM_TESTER ${FILM_SRCS})
#ADD_DEPENDENCIES(FILM_TESTER ${FILM_SRCS})