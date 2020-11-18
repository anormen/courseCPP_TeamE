#include<iostream>
#include "calcRPM.hpp"
//#include "frames.hpp"

calcRPM::calcRPM()
{
    this->acc_inc_delta = 0;
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
    float gear_ratio = 4;
    int oldGearratio = 1;

    //if (startstop == StartButtonSts::PRESSED && info == DriverInformation::NO_MSG)
    //    this->eng_on = !eng_on;

 //   if (this->rpm >= 3000)
 //   {
 //       rpm = rpm * ((gear_ratio - 1) / gear_ratio); //
 //       gear_ratio = gear_ratio - 1;
 //       target_rpm -= 750;
 //   }
   if (oldGearratio =! _gearRatio)
   {
       rpm = rpm * (oldGearratio/_gearRatio);
       target_rpm -= 750;
       oldGearratio = _gearRatio;
   }

    std::cout << "RPM = " << this->rpm << " target_rpm = " << target_rpm << std::endl;
    std::cout << "acc_ped = " << acc_ped << " acc_ped_stored = " << acc_ped_stored << std::endl;
    if (acc_ped != acc_ped_stored)
    {
        increasing_rpm = acc_ped > acc_ped_stored;
        decreasing_rpm = acc_ped < acc_ped_stored;
        target_rpm = acc_ped * 75 * gear_ratio / 2; // should be based on acc_ped. gear?
    }

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

            if (acc_inc_delta > response_time)
                this->rpm += 100 * acc_ped / 20;
        }

        if (decreasing_rpm)
        {
            this->rpm -= 75 * 40 / 50; // how should we calculate decrease rate?
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