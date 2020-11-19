#include <iostream>
#include <unistd.h>
#include <mutex>
#include <future>
#include "can_class.hpp"
#include "ECM.hpp"
#include "frames.hpp"

namespace fr=frames;

int main()
{
    canHandler can;
    can_frame frame;
    can.canInit("vcan0");
    fr::frame_100 data_100;
    fr::frame_200 data_200;
    fr::frame_300 data_300;
    ECM ecm;
    bool isRun = true;

    std::thread IO_thread([&]() {
        while (isRun)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(fr::fr100_updateRate));
            std::cout << "read frame" << std::endl;; 
            while(can.canReadFrame(frame) > 0){ //check if new data available
                can.printFrame(frame);

                if (frame.can_dlc > 0 && frame.can_id != 0)
                {
                    std::lock_guard<std::mutex> guard(data_100.fr100_mutex);
                    if (frame.can_id == 100)
                        memcpy(data_100.get_frame_ptr(), &frame, sizeof(frame));
                    else if (frame.can_id == 300)
                        memcpy(data_300.get_frame_ptr(), &frame, sizeof(frame));
                    //else
                    //do nothing
                }
            }
            if (data_100.get_mode() == fr::SimulationMode::OFF)
            {
                isRun = false;
                std::cout << "Exit IO thread" << std::endl;
            }

            {
                std::lock_guard<std::mutex> guard(data_200.fr200_mutex);
                memcpy(&frame, data_200.get_frame_ptr(), sizeof(frame));
                if(can.canWriteFrame(frame) > 0){
                    std::cout << "write frame" << std::endl;
                    can.printFrame(frame);
                }                    
                else
                    std::cout << "write frame failed" << std::endl;
            }
        }
    });

    while (isRun)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(fr::fr200_updateRate));

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
                std::cout << "\033c \033[0;32m" ; // clear screen
                {
                    std::lock_guard<std::mutex> guard_read(data_100.fr100_mutex);
                    ecm.Update(data_100, data_300);   
                }   
            
                {
                    std::lock_guard<std::mutex> guard_write(data_200.fr200_mutex);
                    ecm.Write(data_200);
                }
                break;
            default:
                isRun = false;
        }
    }
    return 0;
}