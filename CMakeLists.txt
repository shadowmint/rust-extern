# Copyright 2014 Douglas Linder
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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
