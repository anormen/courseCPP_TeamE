#ifndef _CAN_CLASS_H_
#define _CAN_CLASS_H_ 
#include <unistd.h>
#include <linux/can.h>
//#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <cstring>

class canHandler{

    public:
        canHandler(){ startTime = std::chrono::steady_clock::now();};
        bool canInit(const char*);
        int16_t canReadFrame(can_frame&);
        int16_t canWriteFrame(can_frame&);
        void printFrame(const can_frame&);
        ~canHandler() { close(canSocket); };
    private:       
        int16_t canSocket;
        std::chrono::time_point<std::chrono::steady_clock> startTime;
};

#endif