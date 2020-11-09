cmake_minimum_required(VERSION 3.5.1)
project(simulator)
include_directories(share)
add_executable(inputHandler src/inputHandler/main.cpp src/inputHandler/key_converter.cpp src/inputHandler/conversion.cpp share/can_class.cpp)
target_link_libraries(inputHandler PRIVATE ncurses) # should it be PRIVATE?
add_executable(ECM src/ECM/main.cpp src/ECM/ECM.cpp share/can_class.cpp src/TCM/TCM.cpp)
add_executable(displayHandler src/displayHandler/main.cpp src/displayHandler/display_class.cpp share/can_class.cpp src/displayHandler/display_handler.cpp src/displayHandler/data_class.cpp) 
