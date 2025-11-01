# tests/CMakeLists.txt

add_custom_target(check
  COMMAND bash ${CMAKE_CURRENT_LIST_DIR}/test-md5.sh $<TARGET_FILE:rhasher>
  COMMAND bash ${CMAKE_CURRENT_LIST_DIR}/test-sha1.sh $<TARGET_FILE:rhasher>
  DEPENDS rhasher
  COMMENT "Running custom tests (md5, sha1)"
)
