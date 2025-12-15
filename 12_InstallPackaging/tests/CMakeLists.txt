cmake_minimum_required(VERSION 3.10)

enable_testing()

find_package(PkgConfig REQUIRED)
pkg_check_modules(CHECK REQUIRED check)

set(TEST_SOURCES
  test_binary.c
  test_hex.c
  test_roman.c
  test_symbol.c
)

set(TEST_TARGETS "")

foreach(src ${TEST_SOURCES})
  get_filename_component(test_name ${src} NAME_WE)

  add_executable(${test_name} ${src})

  target_link_libraries(${test_name} PRIVATE numberlib ${CHECK_LIBRARIES})

  target_include_directories(${test_name} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CHECK_INCLUDE_DIRS}
  )

  target_link_directories(${test_name} PRIVATE ${CHECK_LIBRARY_DIRS})
  target_compile_options(${test_name} PRIVATE ${CHECK_CFLAGS_OTHER})
  target_link_options(${test_name} PRIVATE ${CHECK_LDFLAGS_OTHER})

  add_test(NAME ${test_name} COMMAND $<TARGET_FILE:${test_name}>)

  list(APPEND TEST_TARGETS ${test_name})
endforeach()

add_custom_target(run_tests
  COMMAND $<TARGET_FILE:test_binary>
  COMMAND $<TARGET_FILE:test_hex>
  COMMAND $<TARGET_FILE:test_roman>
  COMMAND $<TARGET_FILE:test_symbol>
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS ${TEST_TARGETS}
  COMMENT "Running unit tests"
  VERBATIM
)
