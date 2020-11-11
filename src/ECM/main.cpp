#include <iostream>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <future>
#include "can_class.h"
#include "ECM.hpp"
#include "../TCM/TCM.hpp"
#include "frames.hpp"
#include "message_handler.hpp"

int main()
{
    // Sometimes exits without reason...

    fr100 data_read;
    fr200 data_write;

    message_handler msg_handler;
    ECM ecm = ECM();
    TCM tcm = TCM();

    SimulationMode mode;

    std::cout << "before threads\n";
    msg_handler.fr100_input_thread(data_read);
    msg_handler.fr200_output_thread(data_write);
    std::cout << "before while\n";

    while (true)
    {

        if (data_read.candlc > 0)
        {
            mode = static_cast<SimulationMode>(data_read.mode);

            if (mode == SimulationMode::OFF)
            {
                //msg_handler.stop();
                break;
            }
    
            if (mode == SimulationMode::ACTIVE)
            {
                ecm.UpdateECM(data_read.accelerator, data_read.startstop);

                data_write.rpm = ecm.GetRPM();

                std::cout << "ECM acc_ped = " << (int)data_read.accelerator << " RPM = " << data_write.rpm << " gear = " << tcm.GetGear() << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(fr200_updateRate));
    }

    return 0;
}
