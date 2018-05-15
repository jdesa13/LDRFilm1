cmake_minimum_required(VERSION 2.8.9)
project (LDR_Film)

##############################################################
# Output paths
##############################################################
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

#Check to make sure the project was cloned correctly with submodules
if(NOT IS_DIRECTORY "${CMAKE_SOURCE_DIR}/external_libraries/stb")
  message(FATAL_ERROR "The STB submodule directory is missing! "
    "You probably did not clone the project with --recursive, or first checked out "
    "pbrt before it was added. It is possible to recover by running "
    "\"git submodule update --init --recursive\"")
endif()



set(STB_INCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/external_libraries/stb)

set(CNPY_INCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/external_libraries/cnpy)

set(ZLIB_INCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/external_libraries/zlib)

set(GREGAR_INCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/include/)

set(FILM_INCLUDE_DIR
    ${CMAKE_SOURCE_DIR}/src/film)

set(CORE_INLCUDE_DIR
    ${CMAKE_SOURCE_DIR}/src/core)

add_subdirectory(src/core)
add_subdirectory(src/film)

include_directories(${FILM_INCLUDE_DIR} ${CORE_INLCUDE_DIR} ${STB_INCLUDE_DIR} 
                    ${GREGAR_INCLUDE_DIR} ${CNPY_INCLUDE_DIR} ${ZLIB_INCLUDE_DIR})
add_executable(LDR_Tester main.cpp)

target_link_libraries(LDR_Tester film core)

ADD_DEPENDENCIES(LDR_Tester film core)