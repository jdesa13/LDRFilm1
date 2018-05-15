set(FILM_SRCS
    ${GREGAR_INCLUDE_DIR}/Gregar_v.01/film.h film.cpp
    ${GREGAR_INCLUDE_DIR}/Gregar_v.01/ldrfilm.h ldrfilm.cpp
    ${GREGAR_INCLUDE_DIR}/Gregar_v.01/numfilm.h numfilm.cpp)


SET(LIB_TYPE STATIC)

include_directories(
	${STB_INCLUDE_DIR} 
	${GREGAR_INCLUDE_DIR} 
	${CNPY_INCLUDE_DIR} 
	${ZLIB_INCLUDE_DIR}
	)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/lib)



add_library(film ${LIB_TYPE} ${FILM_SRCS})


set(FILM_DEPENDENCIES core film cnpy)

add_executable(FILM_TESTER unit_test_film.cpp)

target_link_libraries(FILM_TESTER film core z ${FILM_DEPENDENCIES})
ADD_DEPENDENCIES(FILM_TESTER film ${FILM_DEPENDENCIES})