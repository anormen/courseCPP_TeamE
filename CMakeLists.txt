cmake_minimum_required(VERSION 3.5.1)
project(simulator)
include_directories(share)
add_executable(inputHandler src/inputHandler/main.cpp share/socketcan_cpp.cpp)
target_link_libraries(inputHandler PRIVATE X11) # should it be PRIVATE?
add_executable(ECM src/ECM/main.cpp src/ECM/main.cpp)
