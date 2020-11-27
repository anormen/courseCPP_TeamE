#include "message_handler.hpp"

message_handler::message_handler()
{
    if(can.canInit("vcan0")) exit(1);
}

void message_handler::IO_read(fr::frameVector &read_frames)
{
    while (can.canReadFrame(frame) > 0)
    { //check if new data available
        can.printFrame(frame);
        if (frame.can_dlc > 0 && frame.can_id != 0)
        {
            for (auto &frm : read_frames)
            {
                if (frame.can_id == frm->get_id())
                {
                    std::lock_guard<std::mutex> guard(read_mutex);
                    memcpy(frm->get_frame_ptr(), &frame, sizeof(frame));
                }
            }
        }
    }
}

void message_handler::IO_write(const fr::frameVector &write_frames)
{
    
    for (const auto &frm : write_frames)
    {
        {
            std::lock_guard<std::mutex> guard(write_mutex);
            memcpy(&frame, frm->get_frame_ptr(), sizeof(frame));
        }
        if (can.canWriteFrame(frame) > 0)
        {
            //can.printFrame(frame);
        }
        else
            std::cout << "write frame failed" << std::endl;
    }
}