#include <iostream>
#include <curses.h>
#include <chrono>
#include <thread>  
#include "can_class.h"
//#include "frames.hpp"
#include "conversion.hpp"
#include "key_converter.hpp"

namespace kc=key_conv;

int main()
{
    can_frame frame;
    canHandler can;
    can.canInit("vcan0");

    Conversion conv;
    kc::keyConverter keyConv;
    kc::UserReq userReq; //Make more local??

    while (1)
    {
        userReq = keyConv.readInputReq();
        conv.fillFrame(frame, userReq);
        uint16_t b = can.canWriteFrame(frame);
        if(b!=sizeof(frame))
            std::cout << "ERROR sending can frame\n\r";

        std::this_thread::sleep_for(std::chrono::milliseconds(fr100_updateRate));

        if(conv.GetSimulationMode() == SimulationMode::OFF)
            break;        
    }

    return 0;

}