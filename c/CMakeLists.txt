## Project
cmake_minimum_required(VERSION 2.8)
project(extern)

# Library setup
file(GLOB_RECURSE SOURCES *.c)

# Flags
if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_C_FLAGS "-Wall -pedantic -Wimplicit-function-declaration -Wreturn-type -Wstrict-prototypes -Wextra")
  if(NOT WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
  endif()
  if(WIN32)
    set(CMAKE_C_LINKER_FLAGS "-static-libgcc -static-libstdc++")
  endif()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
endif()
if(APPLE)
  if("${CMAKE_OSX_ARCHITECTURES}" EQUAL "")
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
  endif()
endif()

# Build library (dynamic)
add_library(extern SHARED ${SOURCES})
set_target_properties(extern PROPERTIES OUTPUT_NAME extern)
set_target_properties(extern PROPERTIES BUILD_WITH_INSTALL_RPATH 1 INSTALL_NAME_DIR "@rpath")

# Build library (static)
add_library(extern_static STATIC ${SOURCES})

## Install rules
if(NOT INSTALL_DIR)
  set(INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/release)
endif()
install(TARGETS extern DESTINATION "${INSTALL_DIR}")
install(TARGETS extern_static DESTINATION "${INSTALL_DIR}")
