#include "display_handler.hpp"
#include "data_class.hpp"
#include <thread>

std::mutex guard;

displayHandler::displayHandler(){

    memset(&frameGen,0,sizeof(frameGen)); //clear generic can frame
    canHndl.canInit(); //init can comm (get socket) 
    dispHndl.initDisplay(); //fake
    futureDisplay = finishedDisplay.get_future();
    futureReader = finishedReader.get_future();

    std::thread reader( [&](){  //start can reader thread

        finishedReader.set_value_at_thread_exit();
        while(dispHndl.getValueMode() != SimulationMode::OFF){ //run as song as mode != off (3)
            if(canHndl.canReadFrame(frameGen) != -1){ //print frame if any data
                canHndl.printFrame(frameGen);
                std::lock_guard<std::mutex> lock(guard); //block write to frame during display
                    dataHndl.processInput(dispHndl, frameGen);  
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(150)); 
        }
    });
    reader.detach();

    std::thread display( [&](){

        finishedDisplay.set_value_at_thread_exit();
        while(dispHndl.getValueMode() != SimulationMode::OFF){
            { // fake scope to release lock
                std::lock_guard<std::mutex> lock(guard);
                    dispHndl.update();  
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(400));                   
        }
    });
    display.detach();
};

bool displayHandler::run(){

    bool isRunning = true;

        if(this->futureReader.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready &&      
            this->futureDisplay.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
                isRunning = false;

    return isRunning;
};