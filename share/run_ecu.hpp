#include <iostream>
#include <unistd.h>
#include "frames.hpp"
#include "message_handler.hpp"

template <class T>
bool run_ecu(T &ecu, const std::vector<fr::base_frame *> read_vec, std::vector<fr::base_frame *> write_vec, message_handler &msg)
{
    bool isRun = true;
    frames::SimulationMode mode;
    for (auto &frm : read_vec){
        if(frm->get_id() == 100)
            mode = static_cast<frames::frame_100 *>(frm)->get_mode();
    }

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
            std::lock_guard<std::mutex> guard_read(msg.read_mutex);
            ecu.Read(read_vec);
        }
        ecu.Update();
        {
            std::lock_guard<std::mutex> guard_write(msg.write_mutex);
            ecu.Write(write_vec);
        }
        break;
    default:
        isRun = false;
    }
    return isRun;
}