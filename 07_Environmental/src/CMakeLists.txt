find_path(RHASH_INCLUDE_DIR NAMES rhash.h)
find_library(RHASH_LIBRARY NAMES rhash librhash)

if(NOT RHASH_LIBRARY OR NOT RHASH_INCLUDE_DIR)
  message(FATAL_ERROR "Required library 'rhash' not found")
else()
  message(STATUS "Library librhash - found")
endif()

set(LIBRARIES ${RHASH_LIBRARY})

set(HAVE_READLINE 0)
if(READLINE)
  find_path(READLINE_INCLUDE_DIR NAMES readline/readline.h)
  find_library(READLINE_LIBRARY NAMES readline)

  if(READLINE_INCLUDE_DIR AND READLINE_LIBRARY)
    message(STATUS "Libreadline found")
    list(APPEND LIBRARIES ${READLINE_LIBRARY})
    set(HAVE_READLINE 1)
  else()
    message(STATUS "Libreadline not found")
  endif()
else()
  message(STATUS "Readline disabled")
endif()

add_executable(rhasher rhasher.c)

target_include_directories(rhasher PRIVATE ${RHASH_INCLUDE_DIR})
if(HAVE_READLINE)
  target_include_directories(rhasher PRIVATE ${READLINE_INCLUDE_DIR})
  target_compile_definitions(rhasher PRIVATE HAVE_READLINE=1)
endif()

target_link_libraries(rhasher PRIVATE ${LIBRARIES})
