cmake_minimum_required(VERSION 2.8.9)
project (LDR_Film)

##############################################################
# Output paths
##############################################################
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set(FILM_INCLUDE_DIR
    ${CMAKE_SOURCE_DIR}/src/film)

set(CORE_INLCUDE_DIR
    ${CMAKE_SOURCE_DIR}/src/core)

set(H_INLCUDE_DIR
    ${CMAKE_SOURCE_DIR}/include/Gregar_v.01)

add_subdirectory(src/film)
add_subdirectory(src/core)

include_directories(${FILM_INCLUDE_DIR} ${CORE_INLCUDE_DIR} ${H_INLCUDE_DIR})
add_executable(LDR_Tester main.cpp)

target_link_libraries(LDR_Tester film)
target_link_libraries(LDR_Tester core)

ADD_DEPENDENCIES(LDR_Tester film)
ADD_DEPENDENCIES(LDR_Tester core)