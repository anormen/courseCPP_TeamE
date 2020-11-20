#include "ECM.hpp"

ECM::ECM()
{
    this->eng_on = false;
    this->temp = 10;
    this->stored_button = fr::StartButtonSts::UNPRESSED;
}

void ECM::Update(fr::frame_100 &frm_100, fr::frame_300 &frm_300)
{

    di.update(frm_100, rpm, infoMsg);

    if (frm_100.get_startstop() != stored_button && infoMsg == fr::DriverInformation::NO_MSG && frm_100.get_mode() == fr::SimulationMode::ACTIVE){
        this->eng_on = !eng_on;
        stored_button = frm_100.get_startstop();
    }

    rpm = rpm_class.CalculateRPM(frm_100.get_accelerator(), frm_300.get_gearratio(), eng_on);
    fuel_class.CalculateFuel(frm_100.get_accelerator(), rpm, frm_300.get_speed());
    CalculateTemp();
}

void ECM::Write(fr::frame_200 &frm_200)
{
    frm_200.set_rpm(rpm);
    frm_200.set_fuelavg(fuel_class.getFuelAvg());
    frm_200.set_fuelinst(fuel_class.getFuelInst());
    frm_200.set_driverinfor(infoMsg);
    frm_200.set_temp(this->temp);
    frm_200.set_updatebit(1);
}

void ECM::CalculateTemp()
{
    counter++;
    if (counter % 5 == 0)
    {
        if (rpm > 0)
            this->temp += this->rpm / 900;
        else
            this->temp -= 2;

        this->temp = std::min((int)this->temp, 127);
        this->temp = std::max((int)this->temp, 10);

        std::cout << "Temp = " << (int)this->temp << std::endl;

        counter = 0;
    }

    std::cout << "Temp = " << (int)this->temp << std::endl;
}