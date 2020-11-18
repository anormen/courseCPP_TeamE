cmake_minimum_required(VERSION 3.5.1)
project(simulator)

set(PROJECT_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INPUT_HANDLER_DIR "${PROJECT_SRC_DIR}/inputHandler")
set(DISPLAY_HANDLER_DIR "${PROJECT_SRC_DIR}/displayHandler")
set(ECM_DIR "${PROJECT_SRC_DIR}/ECM")
set(TCM_DIR "${PROJECT_SRC_DIR}/TCM")
set(SHARE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/share")

include_directories(${SHARE_DIR})

add_library(canIO ${SHARE_DIR}/can_class.cpp)
add_executable(inputHandler ${INPUT_HANDLER_DIR}/main.cpp ${INPUT_HANDLER_DIR}/key_converter.cpp ${INPUT_HANDLER_DIR}/conversion.cpp ${SHARE_DIR}/frames.cpp)
target_link_libraries(inputHandler PRIVATE ncurses pthread canIO) # should it be PRIVATE?

add_executable(ECM ${ECM_DIR}/main.cpp ${ECM_DIR}/ECM.cpp ${ECM_DIR}/calcFuel.cpp ${ECM_DIR}/driverInfo.cpp ${ECM_DIR}/calcRPM.cpp ${SHARE_DIR}/frames.cpp 
        ${TCM_DIR}/gearbox.cpp) 
target_link_libraries(ECM PRIVATE pthread canIO)

add_executable(displayHandler ${DISPLAY_HANDLER_DIR}/main.cpp ${DISPLAY_HANDLER_DIR}/display_class.cpp ${DISPLAY_HANDLER_DIR}/display_handler.cpp 
            ${DISPLAY_HANDLER_DIR}/data_class.cpp ${SHARE_DIR}/frames.cpp) 
target_link_libraries(displayHandler PRIVATE pthread canIO)

add_executable(TCM ${TCM_DIR}/main.cpp ${TCM_DIR}/TCM.cpp ${TCM_DIR}/gearbox.cpp ${SHARE_DIR}/frames.cpp) 
target_link_libraries(TCM PRIVATE pthread canIO)

#set_target_properties(displayHandler PROPERTIES CXX_STANDARD 17)
add_subdirectory(ext)
add_subdirectory(test)