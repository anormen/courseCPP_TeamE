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
        void update(frame_100 &fr100, frame_200 &fr200);
    private:
        std::chrono::steady_clock::time_point startTime;
        const uint16_t messageDuration = 2000;
};

#endif