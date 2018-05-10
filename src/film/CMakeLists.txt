set(FILM_SRCS
    film.h film.cpp
    ldrfilm.h ldrfilm.cpp
)

SET(LIB_TYPE STATIC)

add_library(film ${LIB_TYPE} ${FILM_SRCS})

add_executable(unit_test_film.cpp)