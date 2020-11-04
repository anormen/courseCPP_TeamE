#include <iostream>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fcntl.h>
#include <chrono>
#include <thread>  
#include "can_class.h"

int main()
{
    canHandler canhndl;

    canhndl.canInit();

    can_frame* canRxptr = canhndl.getRxBuffer();

    while(1){
        canhndl.canReadFrame();
        std::cout << "Data: [" << std::setw(2) << std::setfill('0') << (int)canRxptr->can_id << " " << std::setw(2) << std::setfill('0') << (int)canRxptr->can_dlc << " ";
        for(int i = 0 ; i < 8 ; i++ )
        {
            std::cout << std::setw(2) << std::setfill('0') << std::hex<< (int)canRxptr->data[i] << (i < 7 ? ":" : "");
        }
        std::cout << "]" << std::endl;

        if(canRxptr->can_id == 0x64 && canRxptr->can_dlc > 0)
        {
            std::cout << "decoded CAN data: FR100 Accepedal" << canRxptr->data[0] << std::endl;
        }
        else
        {
            std::cout << "decoded CAN data: FR100 is empty" << std::endl;
        }
        

        std::this_thread::sleep_for(std::chrono::milliseconds(canhndl.cycletime)); //see if take value from can frames?
    }
    return 0;
}
