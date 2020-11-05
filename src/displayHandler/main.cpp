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
#include "display_class.h"

int main()
{
    canHandler canHndl;
    displayHandler dispHndl;    

    canHndl.canInit();
    can_frame* canRxptr = canHndl.getRxBuffer();

    while(1){
        canHndl.canReadFrame();
        canHndl.printFrame(canMode::RX);

        //check frame id, check lenght
        if(canRxptr->can_dlc > 0)
        {
            switch(canRxptr->can_id)
            {       
                case 100: //inpur handler
                    dispHndl.setValueAcc(canRxptr->data[0]);
                    break;
                case 200: //ecm
                    dispHndl.setValueRpm(canRxptr->data[0]);
                    break;
                case 300: //tcm
                    break;
                default:
                    std::cout << "Invalid can frame id" << std::endl;
            }
        }
        else
            std::cout << "can data read buffer is empty" << std::endl;
  
        dispHndl.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(canHndl.cycletime)); //see if take value from can frames?
    }
    return 0;
}
