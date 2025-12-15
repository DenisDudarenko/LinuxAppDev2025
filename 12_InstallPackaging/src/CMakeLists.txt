# shared library
add_library(numberlib SHARED numberlib.c)
target_include_directories(numberlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# executable
add_executable(numberstat numberstat.c)
target_link_libraries(numberstat PRIVATE numberlib)

# gettext
include(CheckLibraryExists)
check_library_exists(intl gettext "" HAVE_LIBINTL)
if(HAVE_LIBINTL)
  target_link_libraries(numberstat PRIVATE intl)
endif()

target_compile_definitions(numberstat PRIVATE
  LOCALEDIR="${CMAKE_BINARY_DIR}/locale"
)
