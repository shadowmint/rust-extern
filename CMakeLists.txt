## Project
cmake_minimum_required(VERSION 2.8)
project(RUST_EXTERN)

## Source files
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

## Run cargo build and get output
execute_process(COMMAND cargo clean WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE CARGO_STDOUT ERROR_VARIABLE CARGO_STDERR)
execute_process(COMMAND cargo build --release WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE CARGO_STDOUT ERROR_VARIABLE CARGO_STDERR)
string(REPLACE "\n" ";" CARGO_RESULTS "${CARGO_STDOUT} ${CARGO_STDERR}")
foreach(CARGO_LINE ${CARGO_RESULTS})
  if("${CARGO_LINE}" MATCHES "^note: library: .*")
    string(REPLACE "note: library: " "" CARGO_LINE ${CARGO_LINE})
    list(APPEND RUST_DEPS ${CARGO_LINE})
  endif()
endforeach()

## Find rust library
file(GLOB RUST_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/target/release/*.a)

add_library(rust_extern STATIC IMPORTED)
set_property(TARGET rust_extern PROPERTY IMPORTED_LOCATION ${RUST_LIBS})

## Finalize...
message("RUST LIBS: ${RUST_LIBS}")
message("RUST DEPS: ${RUST_DEPS}")
add_executable(external ${SOURCES})
target_link_libraries(external rust_extern)
target_link_libraries(external ${RUST_DEPS})
