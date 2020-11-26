#ifndef MESSAGE_HANDLER_HPP
#define MESSAGE_HANDLER_HPP

#include <vector>
#include <thread>
#include "frames.hpp"
#include "can_class.hpp"

namespace fr = frames;

typedef std::vector<fr::base_frame *> frameVector;
typedef int sendFlist;

class message_handler
{
public:
    message_handler() = delete;
    message_handler(sendFlist&);
    void IO_write(const frameVector &write_frames);
    void IO_read(frameVector &read_frames);
    std::mutex read_mutex;
    std::mutex write_mutex;

private:
    canHandler can;
    can_frame frame;
    sendFlist list;
};

#endif //MESSAGE_HANDLER_HPP