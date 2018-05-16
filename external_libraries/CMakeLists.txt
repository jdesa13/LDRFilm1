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



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" PARENT_SCOPE)

#############################################################
# Place Libs and exe files in one Output paths
##############################################################
if(NOT OVERRIDE_OUTPUT_DIRECTORY)
  SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
  SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
  SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
endif()


if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-switch -Wno-tautological-compare -Wno-deprecated-register")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-result")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4275 /wd4267 /wd4244 /wd4477 /wd4996 /wd4800 /wd4334 /wd4251 /wd4305 /wd4302 /wd4311 /wd4018")
endif()



#Build Zlib ##############################################

  # Build zlib (only on Windows)
  SET(ZLIB_BUILD_STATIC_LIBS ON CACHE BOOL " " FORCE)
  SET(ZLIB_BUILD_SHARED_LIBS OFF CACHE BOOL " " FORCE)
  ADD_SUBDIRECTORY(zlib)
IF(WIN32) 
  if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "d")
  endif()
  SET(ZLIB_LIBRARY "${CMAKE_BINARY_DIR}/$(CONFIGURATION)/zlibstatic${CMAKE_DEBUG_POSTFIX}.lib" PARENT_SCOPE)
  SET(ZLIB_ROOT "${CMAKE_BINARY_DIR}/$(CONFIGURATION)" PARENT_SCOPE)
  message(STATUS "ZLIB LIBRARY: " ${ZLIB_LIBRARY})
  message(STATUS "ZLIB ROOT: " ${ZLIB_ROOT})
  SET_PROPERTY(TARGET zlibstatic zlib minigzip example PROPERTY FOLDER "zlib")
  INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/zlib")
  add_definitions(-DWIN32)
ENDIF()

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


##############################################################
# ILMBase
##############################################################
OPTION (NAMESPACE_VERSIONING "Namespace Versioning" OFF)
OPTION (BUILD_SHARED_LIBS "Namespace Versioning" OFF)
ADD_SUBDIRECTORY(openexr/IlmBase)
SET_PROPERTY(TARGET Iex IexMath Half Imath IlmThread HalfTest IexTest IlmThread ImathTest toFloat eLut PROPERTY FOLDER "ILMBase")


##############################################################
# OpenEXR
##############################################################
include_directories(
  openexr/IlmBase/Iex
  openexr/IlmBase/Imath
  openexr/IlmBase/IlmThread
  openexr/IlmBase/Half
  openexr/IlmBase/config
  openexr/IlmBase/Imath
  openexr/OpenEXR/config
  openexr/IlmBase/config
  ${CMAKE_CURRENT_SOURCE_DIR}/zlib
  ${CMAKE_CURRENT_BINARY_DIR}/zlib
)


IF(WIN32)
include_directories(
  openexr/IlmBase/config.windows
  )
ELSE()
include_directories(
  ${CMAKE_BINARY_DIR}/openexr/OpenEXR/config 
  ${CMAKE_BINARY_DIR}/openexr/IlmBase/config
  )
ENDIF()

 IF(WIN32)
   SET(OPENEXR_LIBS IlmImf Imath Half zlibstatic)
 ELSE()
   SET(OPENEXR_LIBS IlmImf Imath Half)
 ENDIF()

SET(EXR_LIBS Iex IlmImf IlmThread)
SET(ILMBASE_PACKAGE_PREFIX "${CMAKE_BINARY_DIR}/$(CONFIGURATION)")

LINK_DIRECTORIES ("${CMAKE_BINARY_DIR}")
SET(BUILD_SHARED_LIBS OFF CACHE BOOL " " FORCE)
SET(NAMESPACE_VERSIONING OFF CACHE BOOL " " FORCE)

ADD_SUBDIRECTORY(openexr/OpenEXR)
SET_PROPERTY(TARGET b44ExpLogTable dwaLookups IlmImfUtilTest IlmImfUtil exrenvmap exrheader IlmImfTest exrmakepreview exrmaketiled exrmultipart exrmultiview exrstdattr IlmImf IlmImfExamples IlmImfFuzzTest PROPERTY FOLDER "openEXR")


IF(WIN32)
add_custom_target(CopyIlmBaseLibs
  COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_BINARY_DIR}/$(CONFIGURATION)/b44ExpLogTable.exe
  ${CMAKE_CURRENT_BINARY_DIR}/openexr/OpenEXR/IlmImf/$(CONFIGURATION)/b44ExpLogTable.exe
   COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_BINARY_DIR}/$(CONFIGURATION)/dwaLookups.exe
  ${CMAKE_CURRENT_BINARY_DIR}/openexr/OpenEXR/IlmImf/$(CONFIGURATION)/dwaLookups.exe 
)
ELSE()
add_custom_target(CopyIlmBaseLibs
  COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_BINARY_DIR}/b44ExpLogTable
  ${CMAKE_CURRENT_BINARY_DIR}/openexr/OpenEXR/IlmImf/b44ExpLogTable
   COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_BINARY_DIR}/dwaLookups
  ${CMAKE_CURRENT_BINARY_DIR}/openexr/OpenEXR/IlmImf/dwaLookups
)
ENDIF()
SET_PROPERTY(TARGET CopyIlmBaseLibs b44ExpLogTable dwaLookups IlmImfUtilTest IlmImfUtil exrenvmap exrheader IlmImfTest exrmakepreview exrmaketiled exrmultipart exrmultiview exrstdattr IlmImf IlmImfExamples IlmImfFuzzTest PROPERTY FOLDER "openEXR")

ADD_DEPENDENCIES(CopyIlmBaseLibs Iex Imath IlmThread Half)
ADD_DEPENDENCIES(CopyIlmBaseLibs b44ExpLogTable dwaLookups)
ADD_DEPENDENCIES(IlmImf CopyIlmBaseLibs)

#Add Exporter to allow to render to a data array in Numpy ##############
include_directories(${CNPY_INCLUDE_DIR} ${ZLIB_INCLUDE_DIR})
add_library(cnpy STATIC "${CNPY_INCLUDE_DIR}/cnpy.cpp")
