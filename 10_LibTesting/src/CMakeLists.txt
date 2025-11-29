add_library(buf SHARED buf.c)
target_include_directories(buf PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(buf PRIVATE -Wall -Wextra)
