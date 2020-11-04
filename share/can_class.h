#ifndef _CAN_CLASS_H_
#define _CAN_CLASS_H_ 

class canHandler{

    public:
        canHandler(){};
        void canInit(void);
        uint16_t canReadFrame();
        uint16_t canWriteFrame();
        ~canHandler() {};
        const int cycletime = 250; //cycletime for can send
    private:
        struct can_frame frameRx;
        struct can_frame frameTx;        
        uint16_t canSocket;
        const char *ifname = "vcan0";

};

#endif