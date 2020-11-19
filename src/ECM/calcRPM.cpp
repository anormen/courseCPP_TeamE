#include <iostream>
#include "calcRPM.hpp"

calcRPM::calcRPM()
{
    this->oldGearratio = 10;
}

uint16_t calcRPM::CalculateRPM(int acc_ped, int _gearRatio, bool eng_on)
{
    int target_rpm = 0;
    _gearRatio = std::max(10, _gearRatio); // protect from zero

    // No magic values move to header
    if (acc_ped == 0)
        target_rpm = 890;
    else if (acc_ped == 10)
        target_rpm = 2500;
    else if (acc_ped == 20)
        target_rpm = 3000;
    else if (acc_ped == 30)
        target_rpm = 3500;
    else if (acc_ped == 40)
        target_rpm = 4000;
    else if (acc_ped == 50)
        target_rpm = 4500;
    else if (acc_ped == 60)
        target_rpm = 5000;
    else if (acc_ped == 70)
        target_rpm = 5500;
    else if (acc_ped == 80)
        target_rpm = 6000;
    else if (acc_ped == 90)
        target_rpm = 6500;
    else if (acc_ped == 100)
        target_rpm = 7000;

    if (oldGearratio != _gearRatio)
    {

        this->rpm = (double)this->rpm * ((double)this->oldGearratio / (double)_gearRatio);
        this->oldGearratio = _gearRatio;
    }

    bool increasing_rpm = target_rpm > this->rpm;
    bool decreasing_rpm = target_rpm < this->rpm;

    if (eng_on == true)
    {
        if (this->rpm < 900)
            this->rpm = 900;

        if (increasing_rpm)
            this->rpm += acc_ped * 10 / _gearRatio;

        if (decreasing_rpm)
            this->rpm -= 60;
    }
    else
    {
        this->rpm = 0;
    }

    return this->rpm;
}