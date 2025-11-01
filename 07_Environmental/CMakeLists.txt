cmake_minimum_required(VERSION 3.10)

project(rhasher C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(READLINE "Build with readline" ON)

enable_testing()
add_subdirectory(src)
add_subdirectory(tests)

add_custom_target(distclean
  COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/*
  COMMENT "Remove trash"
)

set_target_properties(distclean PROPERTIES EXCLUDE_FROM_ALL TRUE)