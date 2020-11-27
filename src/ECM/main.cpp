#include <iostream>
#include <unistd.h>
#include "ECM.hpp"
#include "frames.hpp"
#include "message_handler.hpp"
#include "run_ecu.hpp"

namespace fr = frames;

int main()
{
    fr::frame_100 data_100;
    fr::frame_200 data_200;
    fr::frame_300 data_300;

    message_handler msg;

    ECM ecm;
    bool isRun = true;
    bool isRunMain = true;

    fr::frameVector read_vec;
    read_vec.emplace_back(&data_100);
    read_vec.emplace_back(&data_300);
    fr::frameVector write_vec;
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

    while (isRunMain)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(fr::fr200_updateRate));
        isRunMain = run_ecu<ECM>(ecm, read_vec, write_vec, msg);
    }

    IO_thread.join();

    return 0;
}