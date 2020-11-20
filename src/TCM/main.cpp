#include <iostream>
#include <unistd.h>
#include <mutex>
#include <future>
#include "TCM.hpp"
#include "frames.hpp"
#include "gearbox.hpp"
#include "can_class.hpp"

namespace fr=frames;

int main()
{
    canHandler can;
    can.canInit("vcan0");
    can_frame frame;
    fr::frame_100 data_100;
    fr::frame_200 data_200;
    fr::frame_300 data_300;    
    TCM tcm;
    bool isRun = true;

    std::thread IO_thread([&]() {
        while (isRun)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(fr::fr100_updateRate));
            std::cout << "Read frame" << std::endl;
            while(can.canReadFrame(frame) > 0){
                can.printFrame(frame);
            
                if (frame.can_dlc > 0 && frame.can_id != 0)
                {
                    std::lock_guard<std::mutex> guard(data_100.fr100_mutex);
                    if (frame.can_id == 100)
                        memcpy(data_100.get_frame_ptr(), &frame, sizeof(frame));                        
                    else if (frame.can_id == 200)
                        memcpy(data_200.get_frame_ptr(), &frame, sizeof(frame));
                    //else
                        //do nothing
                }   
            }
            if (data_100.get_mode() == fr::SimulationMode::OFF)
            {
                isRun = false;
                std::cout << "Exit IO thread" << std::endl;
            }
            if (data_100.get_mode() != fr::SimulationMode::SLEEP)
            {
                std::cout << "Write frame" << std::endl;
                std::lock_guard<std::mutex> guard(data_300.fr300_mutex);
                memcpy(&frame, data_300.get_frame_ptr(), sizeof(frame));
                if(can.canWriteFrame(frame) > 0){
                    can.printFrame(frame);
                }                    
                else
                    std::cout << "write frame failed" << std::endl;

            }
            std::cout << "\033c \033[0;32m" ; // clear screen
        }
    });

    while (isRun)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(fr::fr300_updateRate));
        switch(data_100.get_mode())
        {
            case fr::SimulationMode::OFF:
                isRun = false;
                IO_thread.join();
                break;
            case fr::SimulationMode::SLEEP:
                break;
            case fr::SimulationMode::INACTIVE:                
            case fr::SimulationMode::ACTIVE:
                {
                    std::lock_guard<std::mutex> guard_read(data_100.fr100_mutex);
                    tcm.Update(data_100,data_200);   
                }   
            
                {
                    std::lock_guard<std::mutex> guard_write(data_300.fr300_mutex);
                    tcm.Write(data_300);
                }
                break;
            default:
                isRun = false;
        }
        std::cout << "\033c \033[0;32m" ; // clear screen
    }
    return 0;
}