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
        
        //debug
        std::cout << "Data: [" << std::setw(3) << std::setfill('0') << (int)canRxptr->can_id << " " << std::setw(2) << std::setfill('0') << (int)canRxptr->can_dlc << " ";
        for(int i = 0 ; i < 8 ; i++ )            
            std::cout << std::setw(2) << std::setfill('0') << std::hex<< (int)canRxptr->data[i] << (i < 7 ? ":" : "");
        std::cout << "]" << std::endl;

        //check frame id, check lenght
        if(canRxptr->can_dlc > 0)
        {
            switch(canRxptr->can_id)
            {       
                case 100: //inpur handler
                    std::cout << "decoded CAN data: FR100 Accelpedal: " << (int)canRxptr->data[0] << std::endl;
                    break;
                case 200: //ecm
                    std::cout << "decoded CAN data: FR200 RPM: " << (int)canRxptr->data[0] << std::endl;
                    break;
                case 300: //tcm
                    break;
                default:
                    std::cout << "Invalid can frame id" << std::endl;
            }
        }
        else
            std::cout << "can data read buffer is empty" << std::endl;
  
        
        std::this_thread::sleep_for(std::chrono::milliseconds(canhndl.cycletime)); //see if take value from can frames?
    }
    return 0;
}
