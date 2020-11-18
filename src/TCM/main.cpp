#include <iostream>
#include <unistd.h>
#include <mutex>
#include <future>
#include "TCM.hpp"
#include "frames.hpp"
#include "gearbox.hpp"
#include "can_class.hpp"

int main()
{
    canHandler can;
    can.canInit("vcan0");
    can_frame frame;
    frame_100 data_100;
    frame_200 data_200;
    frame_300 data_300;    
    uint8_t sendRate = 0;

    TCM tcm;

    std::thread IO_thread([&]() {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(fr100_updateRate));
            std::cout << "Read frame" << std::endl;
            can.canReadFrame(frame);
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

            if (data_100.get_mode() == SimulationMode::OFF)
            {
                std::cout << "Exit IO thread" << std::endl;
                break;
            }
            if(sendRate > 4)
            {
                std::cout << "Write frame" << std::endl;
                std::lock_guard<std::mutex> guard(data_300.fr300_mutex);
                memcpy(&frame, data_300.get_frame_ptr(), sizeof(frame));
                can.canWriteFrame(frame);
                can.printFrame(frame);
                sendRate = 0;
            }
            else
                sendRate++;

            std::cout << "\033c \033[0;32m" ; // clear screen
        }
    });

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(fr300_updateRate));

        if (data_100.get_mode() == SimulationMode::OFF)
        {
            IO_thread.join();
            break;
        }

        if (data_100.get_mode() == SimulationMode::ACTIVE)
        {
            {
                std::lock_guard<std::mutex> guard_read(data_100.fr100_mutex); // onödigt...? Vart ska den läggas?
                tcm.Update(data_100,data_200);
            }

            {
                std::lock_guard<std::mutex> guard_write(data_300.fr300_mutex); // Onödigt...?
                tcm.Write(data_100, data_200, data_300);
            }
        }
    }
    return 0;
}
