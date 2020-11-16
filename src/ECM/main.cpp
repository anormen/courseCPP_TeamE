#include <iostream>
#include <unistd.h>
#include <mutex>
#include <future>
#include "ECM.hpp"
#include "../TCM/TCM.hpp"
#include "frames.hpp"
#include "message_handler.hpp"

int main()
{
    canHandler can;
    can.canInit("vcan0");
    frame_100 data_read;
    frame_200 data_write;
    can_frame frame_read, frame_write;

    message_handler msg_handler;
    ECM ecm;
    TCM tcm;

    std::thread IO_thread([&]() {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(fr100_updateRate));
            std::cout << "read frame\n";
            can.canReadFrame(frame_read);
            can.printFrame(frame_read);
            
            if (frame_read.can_dlc > 0)
            {
                    std::lock_guard<std::mutex> guard(data_read.fr100_mutex);
                    memcpy(data_read.get_frame_ptr(), &frame_read, sizeof(frame_read));
            }

            if (data_read.get_mode() == SimulationMode::OFF)
            {
                std::cout << "Exit IO thread\n";
                break;
            }

            {
                std::cout << "write frame\n";
                std::lock_guard<std::mutex> guard(data_write.fr200_mutex);
                memcpy(&frame_write, data_write.get_frame_ptr(), sizeof(frame_write));
                uint16_t b = can.canWriteFrame(frame_write);
                can.printFrame(frame_write);
            }

            std::cout << std::endl;
        }
    });

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(fr200_updateRate));

        if (data_read.get_length() > 0)
        {

            if (data_read.get_mode() == SimulationMode::OFF)
            {
                IO_thread.join();
                break;
            }

            if (data_read.get_mode() == SimulationMode::ACTIVE)
            {
                {
                    std::lock_guard<std::mutex> guard_read(data_read.fr100_mutex); // onödigt...? Vart ska den läggas?
                    ecm.UpdateECM(data_read.get_accelerator(), data_read.get_startstop());
                }

                {
                    std::lock_guard<std::mutex> guard_write(data_write.fr200_mutex); // Onödigt...?
                    data_write.set_rpm(ecm.GetRPM());  // move somewhere else...
                }
            }
        }
    }
    return 0;
}
