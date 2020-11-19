#include <iostream>
#include "calcRPM.hpp"
//#include "frames.hpp"

calcRPM::calcRPM()
{
    this->acc_inc_delta = 0;
    this->target_rpm = 0;
    this->oldGearratio = 10;
    /*
    //this->RPM=900;
    this->eng_on = false;
    this->acc_inc_delta = 0;
    this->acc_ped_stored = 0;
    this->gear = 0;
    this->target_rpm = 0; */
}

uint16_t calcRPM::CalculateRPM(int acc_ped, int _gearRatio, bool eng_on)
{

    std::cout << "_gearRatio = " << _gearRatio << "\n";

    // No magic values move to header
    if (acc_ped == 0)
        target_rpm = 900;
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
    else if (acc_ped == 45)
        target_rpm = 7000;

    std::cout << "_gearRatio = " << _gearRatio << " oldGearratio = " <<  oldGearratio << "\n";

    if (oldGearratio != _gearRatio)
    {

        if (_gearRatio >= 10) //protect from 0
        {
            this->rpm = (double)this->rpm * ((double)this->oldGearratio / (double)_gearRatio);
            //this->rpm -=100;
            this->oldGearratio = _gearRatio;
        }
    }

    std::cout << "RPM = " << this->rpm << " target_rpm = " << target_rpm << std::endl;
    std::cout << "acc_ped = " << acc_ped << " acc_ped_stored = " << acc_ped_stored << std::endl;
 
    increasing_rpm = target_rpm > this->rpm;
    decreasing_rpm = target_rpm < this->rpm;

    std::cout << "increasing_rpm = " << increasing_rpm << std::endl;
    std::cout << "decreasing_rpm = " << decreasing_rpm << std::endl;
    std::cout << "eng_on = " << eng_on << std::endl;
    if (eng_on == true)
    {
        if (this->rpm < 900)
            this->rpm = 900;

        if (increasing_rpm)
        {
            this->acc_inc_delta += 100; // not hard code, use some update rate
            std::cout << "acc_inc_delta = " << acc_inc_delta << std::endl;

            if (this->rpm >= target_rpm) // || this->RPM >= max_rpm)
            {
                increasing_rpm = false;
                acc_inc_delta = 0;
            }
            this->rpm += acc_ped * 10 / _gearRatio;
            //if (acc_inc_delta > response_time)
            //    this->rpm += 10;
                //this->rpm += 20 * acc_ped / 20;
        }

        if (decreasing_rpm)
        {
            this->rpm -= 60; // how should we calculate decrease rate?
            if (this->rpm < 900)
            {
                this->rpm = 900;
                decreasing_rpm = false;
            }
            if (this->rpm < target_rpm)
            {
                //this->RPM = target_rpm;
                decreasing_rpm = false;
            }
        }
    }
    else
    {
        this->rpm = 0;
    }
    acc_ped_stored = acc_ped;
    std::cout << "\n\n";

    return this->rpm;
}