#include <iostream>
#include <unistd.h>
#include <mutex>
#include <future>
#include "can_class.hpp"
#include "ECM.hpp"
#include "../TCM/TCM.hpp"
#include "../TCM/gearbox.hpp"
#include "frames.hpp"

int main()
{
    canHandler can;
    can.canInit("vcan0");
    frame_100 data_100;
    frame_200 data_200;
    frame_300 data_300;
    can_frame frame;
    uint8_t sendRate = 0;

    ECM ecm;
    TCM tcm;
    Gearbox gearbox;

    std::thread IO_thread([&]() {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(fr100_updateRate));
            std::cout << "read frame\n";
            can.canReadFrame(frame);
            can.printFrame(frame);

            if (frame.can_dlc > 0)
            {
                std::lock_guard<std::mutex> guard(data_100.fr100_mutex);
                if (frame.can_id = 100)
                    memcpy(data_100.get_frame_ptr(), &frame, sizeof(frame));
                else if (frame.can_id = 300)
                    memcpy(data_300.get_frame_ptr(), &frame, sizeof(frame));
                //else
                //do nothing
            }

            if (data_100.get_mode() == SimulationMode::OFF)
            {
                std::cout << "Exit IO thread\n";
                break;
            }
            if(sendRate > 4)
            {
                std::cout << "write frame\n";
                std::lock_guard<std::mutex> guard(data_200.fr200_mutex);
                memcpy(&frame, data_200.get_frame_ptr(), sizeof(frame));
                uint16_t b = can.canWriteFrame(frame);
                can.printFrame(frame);
            }
            else
                sendRate++;
        }
    });

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(fr200_updateRate));

        if (data_100.get_mode() == SimulationMode::OFF)
        {
            IO_thread.join();
            break;
        }

        if (data_100.get_mode() == SimulationMode::ACTIVE)
        {
            {
                std::lock_guard<std::mutex> guard_read(data_100.fr100_mutex); // onödigt...? Vart ska den läggas?
                //di.update(data_100, data_200);
                //cf.CalculateFuel(data_100, data_200, data_300);
                //ecm.UpdateECM(data_100.get_accelerator(), data_100.get_startstop(), data_200.get_driverinfo());
                gearbox.selectGear(data_100.get_accelerator(), ecm.get_rpm());
                ecm.Update(data_100,data_300, gearbox.getGearRatio(ecm.get_rpm()));
                gearbox.getVehicleSpeed( ecm.get_rpm());

 
                
            }

            {
                std::lock_guard<std::mutex> guard_write(data_200.fr200_mutex); // Onödigt...?
                ecm.Write(data_200);
                //data_200.set_fuelavg(cf.getFuelAvg());
                //data_200.set_fuelinst(cf.getFuelInst());                    
                //data_200.set_rpm(ecm.GetRPM());  // move somewhere else...
            }
        }
    }
    return 0;
}