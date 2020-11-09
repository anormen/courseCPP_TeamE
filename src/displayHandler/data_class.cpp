#include "can_class.h"
#include "display_handler.hpp"
#include "display_class.hpp"
#include "frames.hpp"

void dataLayer::process(display &dhndl, const can_frame &frameGen){

        if(frameGen.can_dlc > 0)
        {
            switch(frameGen.can_id)
            {       
                case 100: //inpur handler
                    memcpy(&frame100, &frameGen, 16);   
                    dhndl.setValueAcc(frame100.accelerator);
                    dhndl.setValueAcc(frame100.accelerator);
                    dhndl.setValueBrake(frame100.brake);  
                    dhndl.setValueMode((SimulationMode)frame100.mode);
                    dhndl.setValueStartStop((StartButtonSts)frame100.startstop);   
                    dhndl.setValueGearLever((GearLeverPos)frame100.gearlever); 
                    dhndl.setValueInputUB(frame100.updatebit);                                                                             
                    break;
                case 200: //ecm
                    memcpy(&frame200, &frameGen, 16);
                    dhndl.setValueRpm(frame200.rpm);
                    dhndl.setValueFuelConsumption(frame200.fuel);
                    dhndl.setValueDriverInfo((DriverInformation)frame200.driverinfo);
                    dhndl.setValueTelltale(frame200.telltale);
                    dhndl.setValueECMUB(frame200.updatebit);
                    break;
                case 300: //tcm
                    memcpy(&frame300, &frameGen, 16);
                    dhndl.setValueVehicleSpeed(frame300.speed);
                    dhndl.setValueGearActual(frame300.gearactual);
                    dhndl.setValueTCMUB(frame300.updatebit);                                        
                    break;
                default:
                    std::cout << "Invalid can frame id" << std::endl;
            }
        }
        else
            std::cout << "Can data read buffer is empty" << std::endl;

    return;
};