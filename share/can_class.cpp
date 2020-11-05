#include "can_class.h"
#include <chrono>
#include <iomanip>

void canHandler::canInit(void){

    struct sockaddr_can addr;
    struct ifreq ifr;
    this->canSocket = socket(PF_CAN, SOCK_RAW, CAN_RAW); //open socket of type can
    if(this->canSocket < 0)
        std::cout << "Socket failed" << std::endl;    

    memcpy(ifr.ifr_name, ifname, sizeof(ifname));
    ioctl(this->canSocket, SIOCGIFINDEX, &ifr);
    fcntl(this->canSocket, F_SETFL, O_NONBLOCK); //can be removed when using separate threads NON_BLOCKING_READ

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    
    int result = bind(this->canSocket, (struct sockaddr *)&addr, sizeof(addr)); //
    if(result < 0)
        std::cout << "Bind failed" << std::endl;

    return;
}

uint16_t canHandler::canReadFrame(can_frame &frame){

    uint16_t nbytes = recv(this->canSocket, &frame, sizeof(struct can_frame), 0);//need to fault handle empty socket

    if (nbytes < 0)
        std::cout << "can raw socket read buffer empty" << std::endl;

    /* paranoid check ... */
    if (nbytes < sizeof(struct can_frame))
        std::cout << "read: incomplete CAN frame" << std::endl;

    return nbytes;
}

uint16_t canHandler::canWriteFrame(const can_frame &frame){

    uint16_t nbytes = send(this->canSocket, &frame, sizeof(struct can_frame), 0); //need to fault handle empty socket

    if (nbytes < 0)
        std::cout << "can raw socket write failed" << std::endl;

    /* paranoid check ... */
    if ((nbytes < sizeof(struct can_frame) || nbytes == 0))
        std::cout << "write: incomplete CAN frame" << std::endl;

    return nbytes; // tbd if needed
}
// print frame for debugging
void canHandler::printFrame(can_frame &frame){

    auto now = std::chrono::steady_clock::now();
    std::cout << "T: " << std::dec << std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    std::cout << " ID: " << std::setw(3) << std::setfill('0') << (int)frame.can_id << " L: " << std::setw(2) << std::setfill('0') << (int)frame.can_dlc << " [ ";
    for(int i = 0 ; i < 8 ; i++ )            
        std::cout << std::setw(2) << std::setfill('0') << std::hex<< (int)frame.data[i] << (i < 7 ? ":" : "");
    std::cout << " ]" << std::dec << std::endl;

    return;
}