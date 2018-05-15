# =======================================================================
#   WARNING    WARNING    WARNING    WARNING    WARNING    WARNING
# =======================================================================
#   Remember to put on SAFETY GOGGLES before looking at this file. You
#   are most certainly not expected to read or understand any of it.
# =======================================================================
# This CMake file is responsible for compiling dependency libraries and
# setting up suitable compiler flags for various platforms. You do not
# need to read or change anything in this file; see CMakeLists.txt 


include(CheckCXXCompilerFlag)
include(CheckCXXSourceRuns)



# Set a default build configuration (Release)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()
string(TOUPPER "${CMAKE_BUILD_TYPE}" U_CMAKE_BUILD_TYPE)

# Enable folders for projects in Visual Studio
if (CMAKE_GENERATOR MATCHES "Visual Studio")
  set_property(GLOBAL PROPERTY USE_FOLDERS ON )
endif()

if (APPLE)
  set(CMAKE_MACOSX_RPATH ON PARENT_SCOPE)
endif()

set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)


#include Zlib 

 IF(WIN32)

  # Build zlib (only on Windows)

  SET(ZLIB_BUILD_STATIC_LIBS ON CACHE BOOL " " FORCE)

  SET(ZLIB_BUILD_SHARED_LIBS OFF CACHE BOOL " " FORCE)

  configure_msvc_runtime()

  ADD_SUBDIRECTORY(zlib)

  SET(ZLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/zlib")

  if(MSVC)

  set(CMAKE_DEBUG_POSTFIX "d")

  endif()

  SET(ZLIB_LIBRARY "${CMAKE_BINARY_DIR}/$(CONFIGURATION)/zlibstatic${CMAKE_DEBUG_POSTFIX}.lib")
 
  SET(ZLIB_ROOT "${CMAKE_BINARY_DIR}/$(CONFIGURATION)")

  message(STATUS "ZLIB LIBRARY: " ${ZLIB_LIBRARY})

  message(STATUS "ZLIB ROOT: " ${ZLIB_ROOT})

  SET_PROPERTY(TARGET zlibstatic zlib minigzip example PROPERTY FOLDER "zlib")

  INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/zlib")

  add_definitions(-DWIN32)

  ENDIF()

include_directories(${NUMPY_INCLUDE_DIR} ${ZLIB_INCLUDE_DIR})
add_library(cnpy STATIC "${NUMPY_INCLUDE_DIR}/cnpy.cpp")


# check for C++11 Support
if (CMAKE_CXX_COMPILER_ID MATCHES "^(GNU|Clang|Intel)$")
  CHECK_CXX_COMPILER_FLAG("-std=c++14" HAS_CPP14_FLAG)
  CHECK_CXX_COMPILER_FLAG("-std=c++11" HAS_CPP11_FLAG)

  if (HAS_CPP14_FLAG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  elseif (HAS_CPP11_FLAG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  else()
    message(FATAL_ERROR "Unsupported compiler -- This project requires C++11 support!")
  endif()

  # Enable link time optimization and set the default symbol
  # visibility to hidden (very important to obtain small binaries)
  if (NOT ${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
    # Default symbol visibility
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
  endif()

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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" PARENT_SCOPE)


#Build TBB ##############################################
include(${TBB_ROOT}/cmake/TBBBuild.cmake)
include_directories(${TBB_INCLUDE_DIR})

# Build Intel TBB with enabled Community Preview Features (CPF).
tbb_build(TBB_ROOT ${TBB_ROOT} CONFIG_DIR TBB_DIR MAKE_ARGS tbb_build_dir=${CMAKE_BINARY_DIR})
message("TBB ROOT : " ${TBB_ROOT}) 
message("TBB CONFIG DIR : " ${TBB_DIR}) 
set(TBB_DIR "${TBB_DIR}" PARENT_SCOPE)

if(MSVC)
execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_BINARY_DIR}/tbb_cmake_build_subdir_release"
       ${CMAKE_BINARY_DIR}/Release)
execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_BINARY_DIR}/tbb_cmake_build_subdir_debug"
       ${CMAKE_BINARY_DIR}/Debug)
endif()
