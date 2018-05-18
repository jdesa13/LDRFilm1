include_directories(
	${STB_INCLUDE_DIR} 
	${GREGAR_INCLUDE_DIR} 
	${CNPY_INCLUDE_DIR} 
	${ZLIB_INCLUDE_DIR}
	${OPENEXR_INCLUDE_DIR}
	${NANO_INCLUDE_DIR}
	)

LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/lib)
	
set(FILM_SRCS
    ${GREGAR_INCLUDE_DIR}/Gregar_v.01/film.h film.cpp
    ${GREGAR_INCLUDE_DIR}/Gregar_v.01/ldrfilm.h ldrfilm.cpp
    ${GREGAR_INCLUDE_DIR}/Gregar_v.01/numfilm.h numfilm.cpp
	${GREGAR_INCLUDE_DIR}/Gregar_v.01/hdrfilm.h hdrfilm.cpp
	${GREGAR_INCLUDE_DIR}/Gregar_v.01/gui.h gui.cpp)


SET(LIB_TYPE STATIC)

add_library(film ${LIB_TYPE} ${FILM_SRCS})


set(FILM_DEPENDENCIES core film cnpy )

ADD_DEPENDENCIES(film ${FILM_DEPENDENCIES})

add_executable(FILM_TESTER unit_test_film.cpp)

  IF(WIN32)
    SET(OPENEXR_LIBS IlmImf Imath Half zlibstatic)
  ELSE()
    SET(OPENEXR_LIBS IlmImf Imath Half)
  ENDIF()


target_link_libraries(FILM_TESTER  ${FILM_DEPENDENCIES} ${OPENEXR_LIBS} ${ZLIB_LIBRARY})
ADD_DEPENDENCIES(FILM_TESTER ${FILM_DEPENDENCIES})