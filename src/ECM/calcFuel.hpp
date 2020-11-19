#ifndef _CALCFUEL_H_
#define _CALCFUEL_H_
#include <cstdint>
#include <cstdlib>
#include <thread>
#include <iostream>
#include <deque>
#include "frames.hpp"

namespace fr=frames;

class calcFuel{

    public:
        calcFuel();
        void CalculateFuel(fr::frame_100 &fr100, uint16_t &rpm, fr::frame_300 &fr300);
        double getFuelInst() { return fuelInst; };
        double getFuelAvg() { return fuelAvg; };
    private:
        struct fuelAvgCon{
            double vSpeed = 50.0;
            double iFuel = 0.001;
        }fA;      
        double CalculateRate(uint8_t &accelerator, uint16_t &rpm, uint16_t &speed);                 
        double fuelAvg = 0; //kept by class
        double fuelInst = 0; //kept by class
        double fuelticks = 0;
        double fuelticksPrev = 0;              
        std::chrono::steady_clock::time_point startTime;
        std::deque<double> fuelInstFilter;
        double fuelInstFilterTime = 500;
        double fuelInstFilterSamples = 10;
        double baseRate = 0.000000333333; // l/rpm @ 750 rpm idle      
        std::deque<struct fuelAvgCon> fuelAvgFilter;
        uint16_t fuelAvgFilterDistance = 1000;
        double fuelAvgFilterSamples = 10; 
        double updateRate = 20.0;  // times per second
};

#endif