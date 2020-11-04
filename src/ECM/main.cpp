#include <iostream>
#include <unistd.h>
#include "can_class.h"
#include "ECM.hpp"

int main()
{

    can_frame *frame_read, *frame_write;
    canHandler can;
    can.canInit();
    
    frame_read = can.getRxBuffer();
    frame_write = can.getTxBuffer();
    frame_write->can_dlc=1;
    frame_write->can_id = 200;

    int acc_ped = 0;

    ECM ecm = ECM();

    while (1)
    {
        can.canReadFrame();
        acc_ped = frame_read->data[0];

        ecm.CalculateRPM(acc_ped);

        std::cout << "ECM acc_ped = " << acc_ped << " RPM = " << ecm.GetRPM() <<  std::endl;

        frame_write->data[0]=ecm.GetRPM();
        uint16_t b = can.canWriteFrame();
        //std::cout << "b = " << b << std::endl;

        usleep(1000000);
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
