#ifndef _CAN_CLASS_H_
#define _CAN_CLASS_H_ 
#include <unistd.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <chrono>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <cstring>

class canHandler{

    public:
        canHandler(){ startTime = std::chrono::steady_clock::now();};
        void canInit();
        int16_t canReadFrame(can_frame &frame);
        int16_t canWriteFrame(const can_frame &frame);
        void printFrame(const can_frame &frame);
        ~canHandler() { close(canSocket); };
    private:       
        uint16_t canSocket;
        std::chrono::time_point<std::chrono::steady_clock> startTime;
        const char *ifname = "vcan0";
};

#endif