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
#include "can_class.h"

void canHandler::canInit(void){

    struct sockaddr_can addr;
    struct ifreq ifr;
    this->canSocket = socket(PF_CAN, SOCK_RAW, CAN_RAW); //open socket of type can

    memcpy(ifr.ifr_name, ifname, sizeof(ifname));
    ioctl(this->canSocket, SIOCGIFINDEX, &ifr);
    fcntl(this->canSocket, F_SETFL, O_NONBLOCK); //can be removed when using separate threads NON_BLOCKING_READ

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    bind(this->canSocket, (struct sockaddr *)&addr, sizeof(addr)); //
    return;
}

uint16_t canHandler::canReadFrame(){

    uint16_t nbytes = recv(this->canSocket, &this->frameRx, sizeof(struct can_frame),0);//need to fault handle empty socket

    if (nbytes < 0)
        std::cout << "can raw socket read buffer empty" << std::endl;

    /* paranoid check ... */
    if (nbytes < sizeof(struct can_frame))
        std::cout << "read: incomplete CAN frame" << std::endl;

    return nbytes;
}

uint16_t canHandler::canWriteFrame(){

    uint16_t nbytes = send(this->canSocket, &this->frameTx, sizeof(struct can_frame),0); //need to fault handle empty socket

    if (nbytes < 0)
        std::cout << "can raw socket write failed" << std::endl;

    /* paranoid check ... */
    if ((nbytes < sizeof(struct can_frame) || nbytes == 0))
        std::cout << "write: incomplete CAN frame" << std::endl;

    return nbytes; // tbd if needed
}