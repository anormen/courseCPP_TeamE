#include "ECM.hpp"

ECM::ECM()
{
    this->eng_on = false;
    this->temp = 10;
}

void ECM::Update(frame_100 &frm_100, frame_300 &frm_300, int _gearRatio)
{

    di.update(frm_100, rpm, infoMsg);
    if (frm_100.get_startstop() == StartButtonSts::PRESSED && infoMsg == DriverInformation::NO_MSG)
        this->eng_on = !eng_on;

    std::cout << "eng_on = " << eng_on << "\n";

    
    rpm = rpm_class.CalculateRPM(frm_100.get_accelerator(), _gearRatio, eng_on);
    fuel_class.CalculateFuel(frm_100, rpm, frm_300);
    CalculateTemp();
    //info = di.getDriverInfoMsg();
}

void ECM::Write(frame_200 &frm_200)
{
    frm_200.set_rpm(rpm);
    frm_200.set_fuelavg(fuel_class.getFuelAvg());
    frm_200.set_fuelinst(fuel_class.getFuelInst());
    frm_200.set_driverinfor(infoMsg);
    frm_200.set_temp(this->temp);
    frm_200.set_updatebit(1);
}

// Temportrily needed for running gearbox within ECM
uint16_t ECM::get_rpm()
{
    return this->rpm;
};

void ECM::CalculateTemp()
{
    counter++;
    if (counter % 20 == 0)
    {
        if (rpm > 0)
            this->temp += this->rpm / 900;
        else
            this->temp -= 2;

        this->temp = std::min((int)this->temp, 90);
        this->temp = std::max((int)this->temp, 10);

        std::cout << "Temp = " << (int)this->temp << std::endl;

        counter = 0;
    }

    std::cout << "Temp = " << (int)this->temp << std::endl;
}