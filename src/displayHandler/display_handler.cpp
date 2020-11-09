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
        if(this->frameGen.can_id != 0)
        {
            canHndl.printFrame(frameGen);
            dataHndl.processInput(dispHndl, frameGen);
        }

        dispHndl.update();  

        if(dispHndl.getValueMode() == SimulationMode::OFF)
            this->setValue_isRunning(false);

        std::this_thread::sleep_for(std::chrono::milliseconds(displayUpdateRate));     
};