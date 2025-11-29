find_package(PkgConfig REQUIRED)
pkg_check_modules(CHECK REQUIRED check)

add_executable(test_init test_init.c)
add_executable(test_push test_push.c)
add_executable(test_pop test_pop.c)
add_executable(test_grow test_grow.c)

set(TESTS test_init test_push test_pop test_grow)

foreach(t ${TESTS})
  target_include_directories(${t} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CHECK_INCLUDE_DIRS}
  )

  target_link_directories(${t} PRIVATE ${CHECK_LIBRARY_DIRS})

  target_link_libraries(${t} PRIVATE
    buf
    ${CHECK_LIBRARIES}
  )

  target_compile_options(${t} PRIVATE
    -Wall -Wextra
    ${CHECK_CFLAGS_OTHER}
  )
endforeach()

add_custom_target(check-tests
  COMMAND $<TARGET_FILE:test_init>
  COMMAND $<TARGET_FILE:test_push>
  COMMAND $<TARGET_FILE:test_pop>
  COMMAND $<TARGET_FILE:test_grow>
  DEPENDS ${TESTS}
  COMMENT "Running tests"
)

add_custom_target(coverage
  DEPENDS check-tests
  COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/src/CMakeFiles/buf.dir
          gcov -b -c -o . buf.c.o
  COMMENT "Coverage"
)
set_target_properties(coverage PROPERTIES EXCLUDE_FROM_ALL TRUE)
