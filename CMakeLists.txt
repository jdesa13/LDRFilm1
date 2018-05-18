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

# Sanitize build environment for static build with C++11
if (MSVC)
  # Disable annoying secure CRT warnings
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS")

  # We'll select the TBB library ourselves
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D__TBB_NO_IMPLICIT_LINKAGE")

  # Parallel build on MSVC (all targets)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

  if (NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")

    # Disable Eigen vectorization for Windows 32 bit builds (issues with unaligned access segfaults)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DEIGEN_DONT_ALIGN")
  endif()

  # Static build
  set(CompilerFlags
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
        CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
  foreach(CompilerFlag ${CompilerFlags})
    string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
  endforeach()
elseif(APPLE)
  # Try to auto-detect a suitable SDK
  execute_process(COMMAND bash -c "xcodebuild -version -sdk | grep MacOSX | grep Path | head -n 1 | cut -f 2 -d ' '" OUTPUT_VARIABLE CMAKE_OSX_SYSROOT)
  string(REGEX REPLACE "(\r?\n)+$" "" CMAKE_OSX_SYSROOT "${CMAKE_OSX_SYSROOT}")
  string(REGEX REPLACE "^.*X([0-9.]*).sdk$" "\\1" CMAKE_OSX_DEPLOYMENT_TARGET "${CMAKE_OSX_SYSROOT}")
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

set(ZLIB_INCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/external_libraries/zlib
  ${CMAKE_BINARY_DIR}/external_libraries/zlib
    )
set(OPENEXR_INCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/external_libraries/openexr/OpenEXR/IlmImf
  ${CMAKE_SOURCE_DIR}/external_libraries/openexr/IlmBase/Imath
  ${CMAKE_SOURCE_DIR}/external_libraries/openexr/IlmBase/Iex
  ${CMAKE_SOURCE_DIR}/external_libraries/openexr/IlmBase/Half
  ${CMAKE_SOURCE_DIR}/external_libraries/openexr/OpenEXR/config.windows
  ${CMAKE_SOURCE_DIR}/external_libraries/openexr/IlmBase/config.windows
  )
  

set(GLFW_INCLUDE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/external_libraries/nanogui/ext/glfw/include)
set(GLAD_INCLUDE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/external_libraries/nanogui/ext/glad/include)
set(NANOVG_INCLUDE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/external_libraries/nanogui/ext/nanovg/src)
set(NANOGUI_INCLUDE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/external_libraries/nanogui/include)

set(TBB_ROOT "${CMAKE_SOURCE_DIR}/external_libraries/tbb")
set(TBB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external_libraries/tbb/include")


add_subdirectory(external_libraries)

add_subdirectory(src/core)
add_subdirectory(src/film)

#include_directories(${FILM_INCLUDE_DIR} ${CORE_INLCUDE_DIR} ${STB_INCLUDE_DIR} 
#                   ${GREGAR_INCLUDE_DIR} ${CNPY_INCLUDE_DIR}${ZLIB_INCLUDE_DIR})

#add_executable(LDR_Tester main.cpp)

#target_link_libraries(LDR_Tester film core)

#ADD_DEPENDENCIES(LDR_Tester film core)