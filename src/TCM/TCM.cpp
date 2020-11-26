#include "TCM.hpp"

TCM::TCM()
{
    this->acc = 0;
    this->rpm = 0;
    for (auto i = 0; i < vehiclespeedfilterSamples; i++)
        vehiclespeedfilter.push_front(0);
}

void TCM::Read(std::vector<fr::base_frame *> read_vec)
{
    for (auto &frm : read_vec)
    {
        if (frm->get_id() == 100)
        {
            this->acc = static_cast<fr::frame_100 *>(frm)->get_accelerator();
            this->gear_lever = static_cast<fr::frame_100 *>(frm)->get_gearlever();
        }
        else if (frm->get_id() == 200)
        {
            this->rpm = static_cast<fr::frame_200 *>(frm)->get_rpm();
        }
        else
        {
            // no more
        }
    }
}

void TCM::Update()
{
    gb.setGearleverPos(this->gear_lever);
    gb.calculateVehicleSpeed(this->acc, this->rpm);
    gb.selectGear(this->acc, this->rpm);
}

void TCM::Write(std::vector<fr::base_frame *> write_vec) //remove frame 200 and change get vehicle speed behaviour
{

    for (auto &frm : write_vec)
    {
        if (frm->get_id() == 300)
        {
            static_cast<fr::frame_300 *>(frm)->set_gearactual(gb.getGear());
            static_cast<fr::frame_300 *>(frm)->set_speed(VehicleSpeedFilter(gb.getVehicleSpeed()));
            static_cast<fr::frame_300 *>(frm)->set_gearratio(gb.getGearRatio());
            static_cast<fr::frame_300 *>(frm)->set_updatebit(1);
        }
    }
}

uint16_t TCM::VehicleSpeedFilter(const uint16_t &speed)
{

    vehiclespeedfilter.pop_back();
    vehiclespeedfilter.push_front(speed);
    uint16_t sum = std::accumulate(vehiclespeedfilter.begin(), vehiclespeedfilter.end(), 0);

    return (sum / vehiclespeedfilterSamples);
}