#ifndef _DRIVERINFO_H_
#define _DRIVERINFO_H_

#include "frames.hpp"
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <iostream>
#include <cstdint>

class driverInfo{

    public:
        driverInfo(){};
        void update();
        DriverInformation getDriverInfoMsg(){ return infoMsg; }; //if need to fetch status
    private:
        uint8_t gearLeverPos(); //fetch values
        uint8_t brakePosition();
        uint8_t modeStatus();
        uint8_t startButtonStatus();
        uint16_t rpmValue();
        void updateInfoMsg();
        DriverInformation infoMsg = DriverInformation::NO_MSG; //maintained by class
        std::chrono::steady_clock::time_point startTime;
        uint16_t messageTime = 0;
        const uint16_t timeoutT = 2000;
};

#endif