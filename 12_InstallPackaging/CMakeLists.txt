
cmake_minimum_required(VERSION 3.10)
project(numtable C)

include(GNUInstallDirs)


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ---------------- Options ----------------
option(BUILD_TESTS "Build and enable unit tests" ON)
option(BUILD_PO    "Build translations (.mo) if gettext tools exist" ON)
option(BUILD_MAN   "Generate man page with help2man if available" ON)
option(BUILD_DOC   "Generate documentation with doxygen if available" ON)

add_subdirectory(src)

if (BUILD_PO)
  add_subdirectory(po)
endif()

if (BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

find_program(HELP2MAN_EXECUTABLE help2man)

if (HELP2MAN_EXECUTABLE)
  set(MAN_NAME "numberstat")
  set(MAN_SECTION "1")
  set(MAN_FILE "${CMAKE_BINARY_DIR}/${MAN_NAME}.${MAN_SECTION}")

  add_custom_command(
    OUTPUT "${MAN_FILE}"
    COMMAND "${HELP2MAN_EXECUTABLE}"
            -N --no-info
            -n "number conversion utility"
            $<TARGET_FILE:numberstat>
            -o "${MAN_FILE}"
    DEPENDS numberstat
    COMMENT "Generating man page ${MAN_FILE}"
    VERBATIM
  )

  add_custom_target(man ALL
    DEPENDS "${MAN_FILE}"
  )

  install(FILES "${MAN_FILE}"
          DESTINATION "${CMAKE_INSTALL_MANDIR}/man${MAN_SECTION}")
else()
  message(STATUS "help2man not found")
endif()

# ---------- doxygen (auto-generate Doxyfile) ----------
find_program(DOXYGEN_EXECUTABLE doxygen)

set(DOXY_PROJECT_NAME   "numberstat")
set(DOXY_PROJECT_BRIEF  "Number conversion library and utility")
set(DOXY_PROJECT_NUMBER "1.0")
set(DOXY_INPUT
"${CMAKE_SOURCE_DIR}/src \
 ${CMAKE_SOURCE_DIR}/tests \
 ${CMAKE_SOURCE_DIR}/docs"
)
set(DOXY_OUTPUT_DIR     "${CMAKE_BINARY_DIR}/doc")

if (DOXYGEN_EXECUTABLE)
  configure_file(
    ${CMAKE_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_BINARY_DIR}/Doxyfile
    @ONLY
  )

  add_custom_target(doc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating Doxygen documentation"
    VERBATIM
  )
else()
  message(STATUS "Doxygen not found")
endif()


# ---------------- distclean ----------------
add_custom_target(distclean
  COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}
  COMMENT "Removing build directory"
)
set_target_properties(distclean PROPERTIES EXCLUDE_FROM_ALL TRUE)

# ---------- uninstall ----------
configure_file(
  ${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
  ${CMAKE_BINARY_DIR}/cmake_uninstall.cmake
  @ONLY
)

add_custom_target(uninstall
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_uninstall.cmake
  COMMENT "Uninstalling project"
)
