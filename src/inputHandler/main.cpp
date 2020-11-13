#include <iostream>
#include <curses.h>
#include <chrono>
#include <thread>  
#include "can_class.h"
//#include "frames.hpp"
#include "conversion.hpp"
#include "key_converter.hpp"

int main()
{
    can_frame frame;
    canHandler can;
    can.canInit("vcan0");

    Conversion conv;
    keyConverter keyConv;
    UserReq userReq; //Make more local??

    while (1)
    {
        userReq = keyConv.readInputReq();
        conv.fillFrame(frame, userReq);
        uint16_t b = can.canWriteFrame(frame);
        if(b!=16)
            std::cout << "ERROR sending can frame\n\r";

        std::this_thread::sleep_for(std::chrono::milliseconds(fr100_updateRate));
    }

    return 0;

}
