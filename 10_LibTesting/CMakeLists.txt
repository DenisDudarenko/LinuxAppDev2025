cmake_minimum_required(VERSION 3.10)
project(buf C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(ENABLE_COVERAGE "Enable gcov coverage" OFF)

if(ENABLE_COVERAGE AND (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang"))
  add_compile_options(--coverage -O0 -g)
  add_link_options(--coverage)
endif()

add_subdirectory(src)
add_subdirectory(tests)
