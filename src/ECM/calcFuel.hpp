#ifndef _CALCFUEL_H_
#define _CALCFUEL_H_
#include <cstdint>
#include <cstdlib>
#include <thread>
#include <iostream>
#include <deque>
#include "frames.hpp"

class calcFuel{

    public:
        calcFuel();
        void update(const fr100 &dataread, fr200 &datawrite ,const fr300 &dataread2);
        uint16_t getFuelInst() { return fuelInst; };
        uint16_t getFuelAvg() { return fuelAvg; };
    private:
        struct fuelAvgCon{
            double vSpeed = 50.0;
            double iFuel = 0.001;
        }fA;       
        uint16_t updateRpm(fr200 &datawrite);
        uint8_t updateAccelerator(const fr100 &dataread);
        uint16_t updateVehicleSpeed(const fr300 &dataread2);  
        void updateFuelAvg(fr200 &datawrite);
        void updateFuelInst(fr200 &datawrite);         
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
};

#endif