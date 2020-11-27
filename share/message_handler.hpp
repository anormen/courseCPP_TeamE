#ifndef MESSAGE_HANDLER_HPP
#define MESSAGE_HANDLER_HPP

#include <vector>
#include <thread>
#include "frames.hpp"
#include "can_class.hpp"

namespace fr = frames;

class message_handler
{
public:
    message_handler();
    void IO_write(const fr::frameVector &);
    void IO_read(fr::frameVector &);
    std::mutex read_mutex;
    std::mutex write_mutex;

private:
    canHandler can;
    can_frame frame;
};

#endif //MESSAGE_HANDLER_HPP