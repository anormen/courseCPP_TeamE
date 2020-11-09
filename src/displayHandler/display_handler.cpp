#include "display_handler.hpp"
#include <thread>

displayHandler::displayHandler(){

    memset(&frameGen,0,sizeof(frameGen));   
    canHndl.canInit();
    dispHndl.initDisplay();
};

void displayHandler::run(){

        uint16_t noOfBytes = canHndl.canReadFrame(frameGen);
        canHndl.printFrame(frameGen);

        if(frameGen.can_dlc > 0 && noOfBytes > 0)
        {
            switch(frameGen.can_id)
            {       
                case 100: //inpur handler
                    memcpy(&frame100, &frameGen, 16);
                    dispHndl.setValueAcc(frame100.accelerator);
                    dispHndl.setValueBrake(frame100.brake);  
                    dispHndl.setValueMode((SimulationMode)frame100.mode);
                    dispHndl.setValueStartStop((StartButtonSts)frame100.startstop);   
                    dispHndl.setValueGearLever((GearLeverPos)frame100.gearlever); 
                    dispHndl.setValueInputUB(frame100.updatebit);                                                                             
                    break;
                case 200: //ecm
                    memcpy(&frame200, &frameGen, 16);
                    dispHndl.setValueRpm(frame200.rpm);
                    dispHndl.setValueFuelConsumption(frame200.fuel);
                    dispHndl.setValueDriverInfo((DriverInformation)frame200.driverinfo);
                    dispHndl.setValueTelltale(frame200.telltale);
                    dispHndl.setValueECMUB(frame200.updatebit);
                    break;
                case 300: //tcm
                    memcpy(&frame300, &frameGen, 16);
                    dispHndl.setValueVehicleSpeed(frame300.speed);
                    dispHndl.setValueGearActual(frame300.gearactual);
                    dispHndl.setValueTCMUB(frame300.updatebit);                                        
                    break;
                default:
                    std::cout << "Invalid can frame id" << std::endl;
            }
        }
        else
            std::cout << "can data read buffer is empty" << std::endl;

        dispHndl.update();   

        std::this_thread::sleep_for(std::chrono::milliseconds(displayUpdateRate));     
};