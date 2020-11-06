#include <iostream>
#include <unistd.h>
#include <thread>
#include "can_class.h"
#include "ECM.hpp"
#include "../TCM/TCM.hpp"
#include "frames.hpp"

int main()
{

    can_frame frame_read, frame_write;
    canHandler can;
    can.canInit();

    fr100 data_read;
    fr200 data_write;

    SimulationMode mode;

    ECM ecm = ECM();
    TCM tcm = TCM();

    while (1)
    {
        can.canReadFrame(frame_read);
        can.printFrame(frame_read);
        memcpy(&data_read,&frame_read,16);
        //acc_ped = data_read.accelerator;
        mode=static_cast<SimulationMode>(data_read.mode);

        while(mode==SimulationMode::INACTIVE) {
            can.canReadFrame(frame_read);
            memcpy(&data_read,&frame_read,16);
        }

        if(mode==SimulationMode::OFF)
            break;

        if(mode==SimulationMode::ACTIVE){
            ecm.CalculateRPM(data_read.accelerator,(StartButtonSts)data_read.startstop);
            data_write.rpm=ecm.GetRPM();
        
            //rpm = tcm.CalculateGear(data_write.rpm); // Why can't I just pass the adress to rpm without return? bit field...
            //gear = tcm.GetGear();

            std::cout << "ECM acc_ped = " << data_read.accelerator << " RPM = " << data_write.rpm << " gear = " << tcm.GetGear() << std::endl;

            memcpy(&frame_write,&data_write,16);
            uint16_t b = can.canWriteFrame(frame_write);
            can.printFrame(frame_write);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(fr200_updateRate));
    }

    return 0;
}
