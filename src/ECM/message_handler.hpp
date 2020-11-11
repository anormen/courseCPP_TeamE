#ifndef _MESSAGE_HANDLER_HPP_
#define _MESSAGE_HANDLER_HPP_

#include "can_class.h"
#include "frames.hpp"
#include <mutex>
#include <future>

class message_handler
{
public:
    ~message_handler();
    message_handler();
    void init_fr200(fr200 &frame200);
    void init_fr100(fr100 &frame100);
    void fr100_input_thread(fr100 &data_read);
    void fr200_output_thread(fr200 &data_write);
    std::mutex data_write_mutex;
    std::mutex data_read_mutex;
private:
    canHandler can;
    can_frame frame_read, frame_write;
    fr100 data_read;
    fr200 data_write;
    SimulationMode mode;
    std::promise<bool> exit;
    std::future<bool> exit_future;// = exit.get_future();
    std::thread write_thread, read_thread;
};

#endif //_MESSAGE_HANDLER_HPP_