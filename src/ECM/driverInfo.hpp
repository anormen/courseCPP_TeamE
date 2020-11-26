#ifndef _DRIVERINFO_H_
#define _DRIVERINFO_H_

#include "frames.hpp"
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <iostream>
#include <cstdint>

namespace fr=frames;

class driverInfo{

    public:
        driverInfo(){};
        fr::DriverInformation update(const fr::StartButtonSts &ss, const fr::SimulationMode &mode, const uint16_t &rpm, const uint8_t &brake, const fr::GearLeverPos &gear_lev);
        fr::DriverInformation getInfoMsg(){ return infoMsg;  };
    private:
        std::chrono::steady_clock::time_point startTime;
        const uint16_t messageDuration = 2000;
        fr::DriverInformation infoMsg;
};

#endif //_DRIVERINFO_H_