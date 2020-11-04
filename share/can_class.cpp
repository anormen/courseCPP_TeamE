#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fcntl.h>
#include <chrono>
#include <thread>  
#include "can_class.h"

int main()
{
    struct can_frame frame;

    int s = canInit();

    while(1){
        int b = canReadFrame(s , frame);
        std::cout << "Data: [" << std::setw(2) << std::setfill('0') << (int)frame.can_id << " " << std::setw(2) << std::setfill('0') << (int)frame.can_dlc << " ";
        for(int i = 0 ; i < 8 ; i++ )
        {
            std::cout << std::setw(2) << std::setfill('0') << std::hex<< (int)frame.data[i] << (i < 7 ? ":" : "");
        }
        std::cout << "]" << std::endl;

        frame.can_dlc = 8;
        frame.can_id = 100;
        frame.data[2] = 0xAA;  frame.data[0] = 0xAA;       
        int v = canWriteFrame(s , frame);

        std::this_thread::sleep_for(std::chrono::milliseconds(cycletime)); //see if take value from can frames?
    }
    return 0;
}

int canInit(void){

    struct sockaddr_can addr;
    struct ifreq ifr;
    int s = socket(PF_CAN, SOCK_RAW, CAN_RAW); //open socket of type can

    memcpy(ifr.ifr_name, ifname, sizeof(ifname));
    ioctl(s, SIOCGIFINDEX, &ifr);
    fcntl(s, F_SETFL, O_NONBLOCK); //can be removed when using separate threads NON_BLOCKING_READ

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    bind(s, (struct sockaddr *)&addr, sizeof(addr)); //
    return s;
}

int canReadFrame(const int _s, can_frame &frame){

    int nbytes = recv(_s, &frame, sizeof(struct can_frame),0);//need to fault handle empty socket

    if (nbytes < 0)
        std::cout << "can raw socket read buffer empty" << std::endl;

    /* paranoid check ... */
    if (nbytes < sizeof(struct can_frame))
        std::cout << "read: incomplete CAN frame" << std::endl;

    return nbytes;
}

int canWriteFrame(const int _s, can_frame &frame){

    int nbytes = send(_s, &frame, sizeof(struct can_frame),0); //need to fault handle empty socket

    if (nbytes < 0)
        std::cout << "can raw socket write failed" << std::endl;

    /* paranoid check ... */
    if ((nbytes < sizeof(struct can_frame) || nbytes == 0))
        std::cout << "write: incomplete CAN frame" << std::endl;

    return nbytes; // tbd if needed
}