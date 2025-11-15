find_program(XGETTEXT xgettext)
find_program(MSGMERGE msgmerge)
find_program(MSGFMT msgfmt)

if(NOT XGETTEXT OR NOT MSGMERGE OR NOT MSGFMT)
  message(WARNING "Gettext not found")
  return()
endif()

set(DOMAIN "guess")

set(POT "${CMAKE_BINARY_DIR}/po/${DOMAIN}.pot")
set(PO  "${CMAKE_CURRENT_LIST_DIR}/ru.po")

set(MO_DIR "${CMAKE_BINARY_DIR}/locale/ru/LC_MESSAGES")
set(MO "${MO_DIR}/${DOMAIN}.mo")

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/po")
file(MAKE_DIRECTORY "${MO_DIR}")

file(STRINGS "${CMAKE_CURRENT_LIST_DIR}/POTFILES.in" POTFILES)
set(SOURCES "")
foreach(f IN LISTS POTFILES)
  list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/${f}")
endforeach()

add_custom_command(
  OUTPUT "${POT}"
  COMMAND ${CMAKE_COMMAND} -E env LC_ALL=C.UTF-8
          ${XGETTEXT} --from-code=UTF-8 -k_ -o "${POT}" ${SOURCES}
  DEPENDS ${SOURCES} "${CMAKE_CURRENT_LIST_DIR}/POTFILES.in"
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  COMMENT "Generating ${DOMAIN}.pot"
)

add_custom_target(pot DEPENDS "${POT}")

add_custom_target(update-po
  COMMAND ${CMAKE_COMMAND} -E env LC_ALL=C.UTF-8
          ${MSGMERGE} -U "${PO}" "${POT}"
  DEPENDS pot
  COMMENT "Updating ru.po"
)

add_custom_command(
  OUTPUT "${MO}"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${MO_DIR}"
  COMMAND ${CMAKE_COMMAND} -E env LC_ALL=C.UTF-8
          ${MSGFMT} -o "${MO}" "${PO}"
  DEPENDS "${PO}" pot
  COMMENT "Checking ${DOMAIN}.mo"
)

add_custom_target(i18n ALL DEPENDS "${MO}")

add_custom_target(i18n-clean
  COMMAND ${CMAKE_COMMAND} -E rm -f "${POT}" "${MO}"
  COMMENT "Remove .pot and .mo"
)

set_target_properties(i18n-clean PROPERTIES EXCLUDE_FROM_ALL TRUE)
