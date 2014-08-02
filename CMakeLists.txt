## Project
cmake_minimum_required(VERSION 2.8)
project(RUST_EXTERN)

## Source files
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

## Run cargo build and get output
execute_process(COMMAND cargo build WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE CARGO_STDOUT ERROR_VARIABLE CARGO_STDERR)
string(REPLACE "\n" ";" CARGO_RESULTS "${CARGO_STDOUT} ${CARGO_STDERR}")
foreach(CARGO_LINE ${CARGO_RESULTS}) 
  if("${CARGO_LINE}" MATCHES "^note: library: .*")
    string(REPLACE "note: library: " "" CARGO_LINE ${CARGO_LINE})
    list(APPEND RUST_DEPS ${CARGO_LINE})
  endif()
endforeach()

## Find rust library
file(GLOB RUST_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/target/*.a)

## Finalize...
message("RUST LIBS: ${RUST_LIBS}")
message("RUST DEPS: ${RUST_DEPS}")
add_executable(test ${SOURCES})
target_link_libraries(test ${RUST_LIBS})
target_link_libraries(test ${RUST_DEPS})
