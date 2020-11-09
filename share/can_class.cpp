#include "can_class.h"

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

    memset(&frame,0 ,sizeof(frame)); //clear frame buffer 
    uint16_t nbytes = recv(this->canSocket, &frame, sizeof(struct can_frame), 0);//need to fault handle empty socket

    if (nbytes < 0)
        std::cout << "Failed to read can buffer" << std::endl;

    if (nbytes == 0)
        std::cout << "Can raw socket read buffer empty" << std::endl; // when blocking call

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
void canHandler::printFrame(const can_frame &frame){

    std::cout << std::dec << "T: "
    << std::setw(6) << std::setfill('0') << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-startTime).count()
    << std::setw(3) << std::setfill('0') << " ID: " << (int)frame.can_id 
    << std::setw(2) << std::setfill('0') << " L: " << (int)frame.can_dlc << " [ ";
    for(int i = 0 ; i < 8 ; i++ )            
        std::cout << std::setw(2) << std::setfill('0') << std::hex<< (int)frame.data[i] << (i < 7 ? ":" : "");
    std::cout << " ]" << std::dec << std::endl;

    return;
}