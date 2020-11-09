#include "display_handler.hpp"
#include "data_class.hpp"
#include <thread>

displayHandler::displayHandler(){

    memset(&frameGen,0,sizeof(frameGen));   
    canHndl.canInit();
    dispHndl.initDisplay();
};

void displayHandler::run(){

        uint16_t noOfBytes = canHndl.canReadFrame(frameGen);
        if(noOfBytes > 0)
            canHndl.printFrame(frameGen);
        dataHndl.process(dispHndl, frameGen);
        dispHndl.update();   

        std::this_thread::sleep_for(std::chrono::milliseconds(displayUpdateRate));     
};