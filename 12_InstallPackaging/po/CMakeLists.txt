set(DOMAIN "numberstat")

set(POT "${CMAKE_BINARY_DIR}/po/${DOMAIN}.pot")
set(PO  "${CMAKE_CURRENT_LIST_DIR}/ru.po")

add_custom_command(
  OUTPUT "${POT}"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/po"
  COMMAND ${CMAKE_COMMAND} -E env LC_ALL=C.UTF-8
          ${XGETTEXT} --from-code=UTF-8 -k_ -o "${POT}"
          --files-from="${CMAKE_CURRENT_LIST_DIR}/POTFILES.in"
  DEPENDS "${CMAKE_CURRENT_LIST_DIR}/POTFILES.in"
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  COMMENT "Generating ${DOMAIN}.pot"
)

add_custom_target(pot DEPENDS "${POT}")
