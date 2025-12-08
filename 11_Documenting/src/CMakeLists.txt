add_executable(guess guess.c)

set(BUILD_LOCALEDIR "${CMAKE_BINARY_DIR}/locale")
target_compile_definitions(guess PRIVATE LOCALEDIR="${CMAKE_BINARY_DIR}/locale")

include(CheckLibraryExists)
check_library_exists(intl gettext "" HAVE_LIBINTL)
if(HAVE_LIBINTL)
  target_link_libraries(guess PRIVATE intl)
endif()
