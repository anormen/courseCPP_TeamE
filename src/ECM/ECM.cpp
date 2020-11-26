#include "ECM.hpp"

ECM::ECM()
{
    this->eng_on = false;
    this->temp = 10;
    this->rpm = 0;
    this->counter = 0;
    this->veh_speed = 0;
    this->acc = 0;
    this->gear_ratio = 0;
    this->updatebit = 0;
    this->brake = 0;
}

void ECM::Read(std::vector<fr::base_frame *> data_vec)
{

    for (auto &frm : data_vec)
    {
        if (frm->get_id() == 100)
        {
            this->acc = static_cast<fr::frame_100 *>(frm)->get_accelerator();
            this->startstop = static_cast<fr::frame_100 *>(frm)->get_startstop();
            this->mode = static_cast<fr::frame_100 *>(frm)->get_mode();
            this->updatebit = static_cast<fr::frame_100 *>(frm)->get_updatebit();
            this->gear_lever = static_cast<fr::frame_100 *>(frm)->get_gearlever();
            this->brake = static_cast<fr::frame_100 *>(frm)->get_brake();
        }
        else if (frm->get_id() == 300)
        {
            this->gear_ratio = static_cast<fr::frame_300 *>(frm)->get_gearratio();
            this->veh_speed = static_cast<fr::frame_300 *>(frm)->get_speed();
        }
        else
        {
            // no more
        }
    }
}

void ECM::Update()
{
    //di.update(this);
    fr::DriverInformation info = di.update(this->startstop, this->mode, this->rpm, this->brake, this->gear_lever); // too many inputs, should probably be a method
    if (this->startstop == fr::StartButtonSts::PRESSED && info == fr::DriverInformation::NO_MSG && this->mode == fr::SimulationMode::ACTIVE)
    {
        this->eng_on = !eng_on;
    }
    rpm = rpm_class.CalculateRPM(this->acc, this->gear_ratio, this->eng_on);
    fuel_class.CalculateFuel(this->acc, this->rpm, this->veh_speed);
    CalculateTemp();
}

void ECM::Write(std::vector<fr::base_frame *> data_vec)
{
    for (auto &frm : data_vec)
    {
        if (frm->get_id() == 200)
        {
            static_cast<fr::frame_200 *>(frm)->set_rpm(this->rpm);
            static_cast<fr::frame_200 *>(frm)->set_fuelavg(fuel_class.getFuelAvg());
            static_cast<fr::frame_200 *>(frm)->set_fuelinst(fuel_class.getFuelInst());
            static_cast<fr::frame_200 *>(frm)->set_driverinfor(di.getInfoMsg());
            static_cast<fr::frame_200 *>(frm)->set_temp(this->temp);
            static_cast<fr::frame_200 *>(frm)->set_updatebit(1);
        }
    }
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

        counter = 0;
    }
}