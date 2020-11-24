#include "can_class.hpp"

bool canHandler::canInit(const char * ifname){

    struct sockaddr_can addr;
    struct timeval timeout = {0, 500};
    bool isFault = false;
    //timeout.tv_sec = 0;
    //timeout.tv_usec = 500;

    struct ifreq ifr;
    this->canSocket = socket(PF_CAN, SOCK_RAW, CAN_RAW); //open socket of type can
    if(this->canSocket < 0){ //need error print out 
        std::cout << "Socket failed" << std::endl; 
        isFault = true;           
    }
    memcpy(ifr.ifr_name, ifname, strlen(ifname)+1);
    ioctl(this->canSocket, SIOCGIFINDEX, &ifr);
    //fcntl(this->canSocket, F_SETFL, O_NONBLOCK); //used if NON_BLOCKING_READ
    setsockopt(this->canSocket, CAN_RAW, SO_RCVTIMEO, &timeout, sizeof(timeout));

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    int16_t result = bind(this->canSocket, (struct sockaddr *)&addr, sizeof(addr)); //
    if(result < 0){          //need error print out 
        std::cout << "Bind failed" << std::endl;
        isFault = true; 
    }
    return isFault;
}

int16_t canHandler::canReadFrame(can_frame &frame){

    memset(&frame,0 ,sizeof(frame)); //clear frame buffer before each read
    int16_t nbytes = recv(this->canSocket, &frame, sizeof(struct can_frame), 0);//need to fault handle empty socket

    if (nbytes < 0)
        std::cout << "can raw socket read failed (emtpy queue or vcan0 not running)" << std::endl;
    else if (nbytes < (int16_t)sizeof(struct can_frame))
        std::cout << "read: incomplete CAN frame, DLC 1-15" << std::endl;

    return nbytes; // tbd if needed
}

int16_t canHandler::canWriteFrame(can_frame &frame){

    int16_t nbytes = send(this->canSocket, &frame, sizeof(struct can_frame), 0); //need to fault handle empty socket

    if (nbytes < 0)
        std::cout << "can raw socket write failed (emtpy queue or vcan0 not running)" << std::endl;
    else if (nbytes < (int16_t)sizeof(struct can_frame))
        std::cout << "write: incomplete CAN frame, DLC 0-15" << std::endl;

    return nbytes; // tbd if needed
}
// print frame for debugging
void canHandler::printFrame(const can_frame &frame){

    std::cout << std::dec << "Time: "
    << std::setw(6) << std::setfill('0') << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-startTime).count()
    << std::setw(3) << std::setfill('0') << " ID: " << (int)frame.can_id << std::setw(2) << std::setfill('0') << " DLC: " << (int)frame.can_dlc << " [";
    for(size_t i = 0 ; i < sizeof(frame.data) ; i++ )            
        std::cout << std::setw(2) << std::setfill('0') << std::hex<< (int)frame.data[i] << (i < sizeof(frame.data)-1 ? ":" : "");
    std::cout << "]" << std::dec << std::endl;

    return;
}
