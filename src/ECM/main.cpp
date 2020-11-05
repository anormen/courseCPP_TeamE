#include <iostream>
#include <unistd.h>
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

    //frame_read = can.getRxBuffer();
    //frame_write = can.getTxBuffer();

    int acc_ped = 0;
    int rpm = 0;
    int gear =1;

    ECM ecm = ECM();
    TCM tcm = TCM();

    while (1)
    {
        can.canReadFrame(frame_read);
        memcpy(&data_read,&frame_read,16);
        acc_ped = data_read.accelerator;
        ecm.CalculateRPM(acc_ped);
        
        data_write.rpm=ecm.GetRPM();
        
        //data_write.rpm = tcm.CalculateGear(data_write.rpm); // Why can't I just pass the adress to rpm without return? bit field...
        //gear = tcm.GetGear();

        std::cout << "ECM acc_ped = " << acc_ped << " RPM = " << data_write.rpm << " gear = " << tcm.GetGear() << std::endl;

        memcpy(&frame_write,&data_write,16);
        uint16_t b = can.canWriteFrame(frame_write);
        
        usleep(100000);
    }

    /*

    Init:
        CAN read
        CAN write
        ECM class

    while( 
        (should be two seperate threads later)
        Read CAN
        convert from can_frame.data
        calc RPM
        convert to can_frame.data
        Write CAN
    )

    clear memory etc
    */
    std::cout << "ECM main\n";
    //First version with pseudo code
}
