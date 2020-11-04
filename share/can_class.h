#ifndef _CAN_CLASS_H_
#define _CAN_CLASS_H_ 
#include <unistd.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fcntl.h>
#include <chrono>
#include <thread>  
class canHandler{

    public:
        canHandler(){};
        void canInit(void);
        uint16_t canReadFrame();
        uint16_t canWriteFrame();
        can_frame* getRxBuffer(){ return &frameRx; };
        can_frame* getTxBuffer(){ return &frameTx; };
        ~canHandler() { close(canSocket); };
        const int cycletime = 250; //cycletime for can send TBD
    private:
        struct can_frame frameRx;
        struct can_frame frameTx;        
        uint16_t canSocket;
        const char *ifname = "vcan0";
};

#endif