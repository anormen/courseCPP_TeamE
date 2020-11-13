#include "can_class.h"
#include "display_handler.hpp"
#include "display_class.hpp"
#include "frames.hpp"

void dataLayer::processInput(display &dHndl, const can_frame &frameGen){

        if(frameGen.can_dlc > 0)
        {
            switch(frameGen.can_id)
            {       
                case 100: //inpur handler
                    memcpy(&frame100, &frameGen, sizeof(frame100));   
                    dHndl.setValueAcc(frame100.accelerator);
                    dHndl.setValueAcc(frame100.accelerator);
                    dHndl.setValueBrake(frame100.brake);  
                    dHndl.setValueMode((SimulationMode)frame100.mode);
                    dHndl.setValueStartStop((StartButtonSts)frame100.startstop);   
                    dHndl.setValueGearLever((GearLeverPos)frame100.gearlever); 
                    dHndl.setValueInputUB(frame100.updatebit);                                                                             
                    break;
                case 200: //ecm
                    memcpy(&frame200, &frameGen, sizeof(frame200));  
                    dHndl.setValueRpm(frame200.rpm);
                    dHndl.setValueFuelConsumptionAvg(frame200.fuelavg);
                    dHndl.setValueFuelConsumptionInst(frame200.fuelinst);                    
                    dHndl.setValueDriverInfo((DriverInformation)frame200.driverinfo);
                    dHndl.setValueTelltale(frame200.telltale);
                    dHndl.setValueECMUB(frame200.updatebit);
                    break;
                case 300: //tcm
                    memcpy(&frame300, &frameGen, sizeof(frame300));  
                    dHndl.setValueVehicleSpeed(frame300.speed);
                    dHndl.setValueGearActual(frame300.gearactual);
                    dHndl.setValueTCMUB(frame300.updatebit);                                        
                    break;
                default:
                    std::cout << "Invalid can frame id" << std::endl;
            }
        }
        else
            std::cout << "Can data read buffer is empty" << std::endl;

    return;
};