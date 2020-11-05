#include <iostream>
#include <unistd.h>
#include "can_class.h"
#include "ECM.hpp"
#include "../TCM/TCM.hpp"
#include "frames.hpp"

int main()
{

    can_frame *frame_read, *frame_write;
    canHandler can;
    can.canInit();

    
    fr100 data_read;
    fr200 data_write;

    frame_read = can.getRxBuffer();
    frame_write = can.getTxBuffer();
    //frame_write->can_dlc=1;
    //frame_write->can_id = 200;

    int acc_ped = 0;
    int rpm = 0;
    int gear =1;

    ECM ecm = ECM();
    TCM tcm = TCM();

    while (1)
    {
        can.canReadFrame();
        //data_read=frame_read->data;
        memcpy(&data_read,frame_read,16);
        acc_ped = data_read.accelerator;
        //acc_ped = frame_read->data[0];
        ecm.CalculateRPM(acc_ped);
        
        data_write.rpm=ecm.GetRPM();
        //tcm.CalculateGear(rpm); // måste ändra rpm i ecm klassen
        //gear = tcm.GetGear();

        std::cout << "ECM acc_ped = " << acc_ped << " RPM = " << data_write.rpm << " gear = " << gear << std::endl;



        memcpy(frame_write,&data_write,16);
        uint16_t b = can.canWriteFrame();



        //std::cout << "b = " << b << std::endl;

        
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
