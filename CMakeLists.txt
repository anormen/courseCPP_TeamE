cmake_minimum_required(VERSION 3.5.1)
project(simulator)
include_directories(share)
add_executable(inputHandler src/inputHandler/main.cpp share/can_class.cpp)
target_link_libraries(inputHandler PRIVATE ncurses) # should it be PRIVATE?
add_executable(ECM src/ECM/main.cpp src/ECM/ECM.cpp)
add_executable(displayHandler src/displayHandler/main.cpp share/can_class.cpp) 
