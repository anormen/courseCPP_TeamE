#include <iostream>
#include <curses.h>
#include <chrono>
#include <thread>  
#include "../../share/can_class.hpp"
#include "conversion.hpp"
#include "key_converter.hpp"

namespace kc=key_conv;

int main()
{
    can_frame frame;
    canHandler can;
    can.canInit("vcan0");

    Conversion convert;
    kc::keyConverter keyConv;
    kc::UserReq userReq; //Make more local??

    while (1)
    {
        userReq = keyConv.readInputReq();
        convert.fillFrame(frame, userReq);
        uint16_t b = can.canWriteFrame(frame);
        if(b != sizeof(frame))
            std::cout << "ERROR sending can frame\n\r";

        std::this_thread::sleep_for(std::chrono::milliseconds(fr100_updateRate*3)); //slowdown sending

        if(convert.GetSimulationMode() == SimulationMode::OFF)
            break;        
    }
    return 0;
}