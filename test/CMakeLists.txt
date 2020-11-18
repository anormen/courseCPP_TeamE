project(simulator)

add_executable(test test_test.cpp ${SHARE_DIR}/frames.cpp)
target_link_libraries(test PRIVATE gtest gtest_main pthread)