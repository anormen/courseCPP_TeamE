#include <iostream>
#include <curses.h>
#include <chrono>
#include <thread>  
#include "can_class.hpp"
#include "conversion.hpp"
#include "key_converter.hpp"

namespace kc=key_conv;
namespace fr=frames;

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
        std::this_thread::sleep_for(std::chrono::milliseconds(fr::fr100_updateRate)); //slowdown sending
        userReq = keyConvert.readInputReq();
        canConvert.fillFrame(frame, userReq); 

        switch (canConvert.GetSimulationMode())
        {
            case fr::SimulationMode::OFF:
                //turn off
                can.canWriteFrame(frame);
                isRun = false;
                break; 
            case fr::SimulationMode::SLEEP:
                //do nothing but wait
                break;
            case fr::SimulationMode::INACTIVE:
            case fr::SimulationMode::ACTIVE:
                //send frames
                can.canWriteFrame(frame); 
                break;
            default:
                //unhandled mode
                isRun = false;
        }
    }
    return 0;
}