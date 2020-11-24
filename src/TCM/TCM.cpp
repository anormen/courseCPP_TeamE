#include "TCM.hpp"


TCM::TCM(){

    for (auto i = 0; i < vehiclespeedfilterSamples; i++)
        vehiclespeedfilter.push_front(0);   
}

void TCM::Update(fr::frame_100 &frm_100, fr::frame_200 &frm_200)
{   
    gb.setGearleverPos(frm_100.get_gearlever());
    gb.calculateVehicleSpeed(frm_100.get_accelerator(), frm_200.get_rpm());
    gb.selectGear(frm_100.get_accelerator(), frm_200.get_rpm());
}

void TCM::Write(fr::frame_300 &frm_300) //remove frame 200 and change get vehicle speed behaviour
{
    //std::cout << "Speed : " << (int)gb.getVehicleSpeed() << std::endl;
    frm_300.set_gearactual(gb.getGear());
    frm_300.set_speed(VehicleSpeedFilter(gb.getVehicleSpeed()));
    frm_300.set_gearratio(gb.getGearRatio());
    frm_300.set_updatebit(1);
}

uint16_t TCM::VehicleSpeedFilter(const uint16_t &speed){

    vehiclespeedfilter.pop_back();
    vehiclespeedfilter.push_front(speed);
    uint16_t sum = std::accumulate(vehiclespeedfilter.begin(), vehiclespeedfilter.end(), 0);

    return (sum / vehiclespeedfilterSamples);
}