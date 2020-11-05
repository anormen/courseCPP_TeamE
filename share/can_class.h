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

enum class canMode : bool { RX , TX };

class canHandler{

    public:
        canHandler(){};
        void canInit(void);
        uint16_t canReadFrame(can_frame &frame);
        uint16_t canWriteFrame(const can_frame &frame);
        void printFrame(can_frame &frame);
        ~canHandler() { close(canSocket); };
        const int cycletime = 250; //cycletime for can send TBD
    private:       
        uint16_t canSocket;
        const char *ifname = "vcan0";
};

#endif