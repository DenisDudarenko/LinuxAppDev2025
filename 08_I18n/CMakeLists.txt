cmake_minimum_required(VERSION 3.10)
project(guess_i18n C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(po)
add_subdirectory(src)

if(TARGET guess AND TARGET i18n)
  add_dependencies(guess i18n)
endif()

add_custom_target(distclean
  COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}
  COMMENT "Remove trash"
)

set_target_properties(distclean PROPERTIES EXCLUDE_FROM_ALL TRUE)
