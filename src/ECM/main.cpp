#include <iostream>
#include <unistd.h>
#include "ECM.hpp"
#include "frames.hpp"
#include "message_handler.hpp"

namespace fr = frames;

int main()
{
    fr::frame_100 data_100;
    fr::frame_200 data_200;
    fr::frame_300 data_300;

    message_handler msg;

    ECM ecm;
    bool isRun = true;

    std::vector<fr::base_frame *> read_vec;
    read_vec.emplace_back(&data_100);
    read_vec.emplace_back(&data_300);

    std::vector<fr::base_frame *> write_vec;
    write_vec.emplace_back(&data_200);

    std::thread IO_thread([&]() {
        while (isRun)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(fr::fr100_updateRate));

            msg.IO_read(read_vec);

            if (data_100.get_mode() == fr::SimulationMode::OFF)
            {
                isRun = false;
                std::cout << "Exit IO thread" << std::endl;
            }

            if (data_100.get_mode() != fr::SimulationMode::SLEEP)
                msg.IO_write(write_vec);
        }
    });

    while (isRun)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(fr::fr200_updateRate));
        switch (data_100.get_mode())
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
                std::lock_guard<std::mutex> guard_read(msg.read_mutex);
                if(data_100.get_updatebit() == 1){
                    ecm.Update(data_100, data_300);
                    data_100.set_updatebit(0);
                }
                
            }
            {
                std::lock_guard<std::mutex> guard_write(msg.write_mutex);
                ecm.Write(data_200);
            }
            break;
        default:
            isRun = false;
        }
        //std::cout << "\033c \033[0;32m"; // clear screen
    }

    return 0;
}