cmake_minimum_required(VERSION 3.10)
project(guess_i18n C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(po)



if(TARGET guess AND TARGET i18n)
  add_dependencies(guess i18n)
endif()

add_custom_target(distclean
  COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}
  COMMENT "Remove trash"
)

set_target_properties(distclean PROPERTIES EXCLUDE_FROM_ALL TRUE)

find_program(DOXYGEN doxygen)
if(DOXYGEN)
  add_custom_target(doc
    COMMAND ${DOXYGEN} ${CMAKE_SOURCE_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating doxygen"
  )
endif()

find_program(HELP2MAN help2man)
if(HELP2MAN)
  add_custom_target(man
    COMMAND ${HELP2MAN} -N --no-info -n "number guessing game"
            $<TARGET_FILE:guess> -o ${CMAKE_SOURCE_DIR}/guess.1
    DEPENDS guess
    COMMENT "Generating man"
  )
endif()