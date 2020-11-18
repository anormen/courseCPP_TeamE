#include <iostream>
#include <curses.h>
#include <chrono>
#include <thread>  
#include "can_class.hpp"
#include "conversion.hpp"
#include "key_converter.hpp"

namespace kc=key_conv;

int main()
{
    can_frame frame;
    canHandler can;
    can.canInit("vcan0");
    bool isRun = true;

    Conversion canConvert;
    kc::keyConverter keyConvert;
    kc::UserReq userReq; //Make more local??

    while (isRun)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(fr100_updateRate)); //slowdown sending
        userReq = keyConvert.readInputReq();
        canConvert.fillFrame(frame, userReq); 

        switch (canConvert.GetSimulationMode())
        {
            case SimulationMode::OFF:
                can.canWriteFrame(frame);
                isRun = false;
                break; 
            case SimulationMode::SLEEP:
                break;
            case SimulationMode::INACTIVE:
            case SimulationMode::ACTIVE:
                can.canWriteFrame(frame); 
                break;
            default:
                std::cout << "Unhandled mode" << std::endl;
        }
    }
    return 0;
}