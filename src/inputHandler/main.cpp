#include <iostream>
#include <chrono>
#include <thread>  
#include "conversion.hpp"
#include "key_converter.hpp"
#include "message_handler.hpp"
#include <vector>
#include <functional>
#include <unordered_map>

namespace kc = key_Converter;
namespace fr = frames;

int main()
{
    message_handler msg;
    fr::frame_100 data_100;
    fr::frameVector write_vec;
    write_vec.emplace_back(&data_100);
    bool isRun = true;
    kc::keyConverter keyConvert;

    while (isRun)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(fr::fr100_updateRate)); //slowdown sending
        kc::UserReq userReq = keyConvert.readKeyInputReq(); //get key from keyboard
        exeRequest(data_100, userReq);  //handle received action

        switch (data_100.get_mode())
        {
            case fr::SimulationMode::OFF:
                //turn off
                msg.IO_write(write_vec);
                isRun = false;
                break; 
            case fr::SimulationMode::SLEEP:
                //do nothing but wait
                break;
            case fr::SimulationMode::INACTIVE:
            case fr::SimulationMode::ACTIVE:
                //send frames
                msg.IO_write(write_vec);
                break;
            default:
                //unhandled mode
                isRun = false;
        }
    }
    return 0;
}