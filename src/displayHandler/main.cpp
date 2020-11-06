//#include <iostream>
//#include <linux/can.h>
//#include <linux/can/raw.h>
//#include <sys/socket.h>
//#include <net/if.h>
//#include <sys/ioctl.h>
//#include <sys/types.h>
//#include <iostream>
//#include <cstring>
//#include <iomanip>
//#include <fcntl.h>
#include <chrono>
#include <thread>  
#include "can_class.h"
#include "display_class.h"
#include "frames.hpp"

const u_int16_t displayUpdateRate = 500;

int main()
{
    canHandler canHndl;
    can_frame fr;
    memset(&fr,0,sizeof(fr));
    displayHandler dispHndl;   
    fr100 frame100;
    fr200 frame200;
    fr300 frame300; 

    canHndl.canInit();

    while(1){
        canHndl.canReadFrame(fr);
        canHndl.printFrame(fr);

        //check frame id, check lenght
        if(fr.can_dlc > 0)
        {
            switch(fr.can_id)
            {       
                case 100: //inpur handler
                    memcpy(&frame100, &fr, 16);
                    dispHndl.setValueAcc(frame100.accelerator);
                    dispHndl.setValueBrake(frame100.brake);  
                    dispHndl.setValueMode((SimulationMode)frame100.mode);
                    dispHndl.setValueStartStop((StartButtonSts)frame100.startstop);   
                    dispHndl.setValueGearLever((GearLeverPos)frame100.gearlever); 
                    dispHndl.setValueInputUB(frame100.updatebit);                                                                             
                    break;
                case 200: //ecm
                    memcpy(&frame200, &fr, 16);
                    dispHndl.setValueRpm(frame200.rpm);
                    dispHndl.setValueFuelConsumption(frame200.fuel);
                    dispHndl.setValueDriverInfo((DriverInformation)frame200.driverinfo);
                    dispHndl.setValueTelltale(frame200.telltale);
                    dispHndl.setValueECMUB(frame200.updatebit);
                    break;
                case 300: //tcm
                    memcpy(&frame300, &fr, 16);
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
        std::this_thread::sleep_for(std::chrono::milliseconds(fr100_updateRate-100)); //see if take value from can frames?
    }
    return 0;
}
