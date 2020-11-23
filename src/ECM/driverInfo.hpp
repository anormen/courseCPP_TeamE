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
        void update(fr::frame_100 &fr100, const uint16_t &rpm, fr::DriverInformation &infoMsg);
    private:
        std::chrono::steady_clock::time_point startTime;
        const uint16_t messageDuration = 2000;
};

#endif