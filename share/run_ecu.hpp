#include <iostream>
#include <unistd.h>
#include "frames.hpp"
#include "message_handler.hpp"

template <class T>
bool run_ecu(T &ecu, const std::vector<fr::base_frame *> read_vec, std::vector<fr::base_frame *> write_vec, std::mutex &read_mutex, std::mutex &write_mutex, const fr::SimulationMode &mode)
{
    bool isRun = true;
    std::cout << "run ecu mode = " << (int)mode << std::endl;
    switch (mode)
    {
    case fr::SimulationMode::OFF:
        isRun = false;
        //IO_thread.join();
        break;
    case fr::SimulationMode::SLEEP:
        break;
    case fr::SimulationMode::INACTIVE:
    case fr::SimulationMode::ACTIVE:
        {
            std::lock_guard<std::mutex> guard_read(read_mutex);
            ecu.Read(read_vec);
        }
        ecu.Update();
        {
            std::lock_guard<std::mutex> guard_write(write_mutex);
            ecu.Write(write_vec);
        }
        break;
    default:
        isRun = false;
    }
    return isRun;
}