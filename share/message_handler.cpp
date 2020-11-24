#include "message_handler.hpp"

message_handler::message_handler()
{
    can.canInit("vcan0");
}

void message_handler::IO_read(std::vector<frames::base_frame *> &read_frames)
{
    while (can.canReadFrame(frame) > 0)
    { //check if new data available
        can.printFrame(frame);
        if (frame.can_dlc > 0 && frame.can_id != 0)
        {
            for (auto &frm : read_frames)
            {
                std::cout << "trying to read " << (int)frm->get_id() << std::endl;
                if (frame.can_id == frm->get_id())
                {
                    std::cout << "reading " << (int)frame.can_id << std::endl;
                    std::lock_guard<std::mutex> guard(read_mutex);
                    memcpy(frm->get_frame_ptr(), &frame, sizeof(frame));
                }
            }
        }
    }
}

void message_handler::IO_write(const std::vector<frames::base_frame *> &write_frames)
{
    
    for (const auto &frm : write_frames)
    {
        {
            std::lock_guard<std::mutex> guard(write_mutex);
            memcpy(&frame, frm->get_frame_ptr(), sizeof(frame));
        }
        if (can.canWriteFrame(frame) > 0)
        {
            std::cout << "write frame" << std::endl;
            can.printFrame(frame);
        }
        else
            std::cout << "write frame failed" << std::endl;
    }
}