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
        void update(const fr100 &dataread, fr200 &datawrite);
        DriverInformation getDriverInfoMsg(){ return infoMsg; }; //if need to fetch status
    private:
        uint8_t gearLeverPos(const fr100 &dataread); //fetch values
        uint8_t brakePosition(const fr100 &dataread);
        uint8_t modeStatus(const fr100 &dataread);
        uint8_t startButtonStatus(const fr100 &dataread);
        uint16_t rpmValue(fr200 &datawrite);
        void updateInfoMsg(fr200 &datawrite);
        DriverInformation infoMsg = DriverInformation::NO_MSG; //maintained by class
        std::chrono::steady_clock::time_point startTime;
        const uint16_t messageDuration = 2000;
};

#endif