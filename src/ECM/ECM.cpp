#include "ECM.hpp"

ECM::ECM()
{
    //this->RPM=900;
    this->eng_on = false;
    this->acc_inc_delta = 0;
    this->acc_ped_stored = 0;
    this->gear = 0;
    this->target_rpm = 0;
}

void ECM::CalculateRPM(int acc_ped)
{

    float gear_ratio = 4;

    if (this->RPM >= shift_rpm)
    {
        RPM = RPM * ((gear_ratio - 1) / gear_ratio); //
        gear_ratio = gear_ratio - 1;
        target_rpm -= 750;
    }

    std::cout << "RPM = " << this->RPM << " target_rpm = " << target_rpm << std::endl;
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
    if (this->eng_on == true)
    {
        if (this->RPM < 900)
            this->RPM = 900;

        if (increasing_rpm)
        {
            this->acc_inc_delta += fr200_updateRate;
            std::cout << "acc_inc_delta = " << acc_inc_delta << std::endl;
            
            if (this->RPM >= target_rpm) // || this->RPM >= max_rpm)
            {
                increasing_rpm = false;
                acc_inc_delta = 0;
            }

            if (acc_inc_delta > response_time)
                this->RPM += 100 * acc_ped / 20;
        }

        if (decreasing_rpm)
        {
            this->RPM -= 75 * 40 / 50; // how should we calculate decrease rate?
            if (this->RPM < 900)
            {
                this->RPM = 900;
                decreasing_rpm = false;
            }
            if (this->RPM < target_rpm)
            {
                //this->RPM = target_rpm;
                decreasing_rpm = false;
            }
        }
    }
    else
    {
        this->RPM = 0;
    }
    acc_ped_stored = acc_ped;
    std::cout << "\n\n";
}

void ECM::UpdateECM(int acc_ped, StartButtonSts startstop)
{
    if (startstop == StartButtonSts::PRESSED)
        this->eng_on = !eng_on;
    //tcm->GetGear();
    this->CalculateRPM(acc_ped);
}

int ECM::GetRPM() { return RPM; }