project(simulator)

add_executable(test1 test_test.cpp ${SHARE_DIR}/frames.cpp)
target_link_libraries(test1 PRIVATE gtest gtest_main pthread)