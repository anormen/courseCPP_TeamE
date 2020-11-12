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
    fr100 data_read;
    fr200 data_write;

    message_handler msg_handler;
    ECM ecm = ECM();
    TCM tcm = TCM();

    SimulationMode mode;

    msg_handler.init_fr100(data_read);
    msg_handler.init_fr200(data_write);

    msg_handler.fr100_input_thread(data_read);
    msg_handler.fr200_output_thread(data_write);

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(fr200_updateRate));
        
        if (data_read.candlc > 0)
        {
            mode = static_cast<SimulationMode>(data_read.mode);

            if (mode == SimulationMode::OFF)
            {
                // Wait for threads to exit
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                break;
            }
    
            if (mode == SimulationMode::ACTIVE)
            {
                {
                std::lock_guard<std::mutex> guard_read(msg_handler.data_read_mutex); // onödigt...? Vart ska den läggas?
                ecm.UpdateECM(data_read.accelerator, data_read.startstop);
                }
                
                {
                std::lock_guard<std::mutex> guard_write(msg_handler.data_write_mutex); // Onödigt...?
                data_write.rpm = ecm.GetRPM(); // move somewhere else
                }
                std::cout << "ECM acc_ped = " << (int)data_read.accelerator << " RPM = " << data_write.rpm << " gear = " << tcm.GetGear() << std::endl;
            }
        }
        
    }
    return 0;
}
