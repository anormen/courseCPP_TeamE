#include "TCM.hpp"

TCM::TCM(){
        for (int i = 0; i < vehiclespeedfilterSamples; i++)
        vehiclespeedfilter.push_front(0.0);   
}

void TCM::Update(fr::frame_100 &frm_100, fr::frame_200 &frm_200)
{   
    gb.setGearleverPos(frm_100.get_gearlever());
    gb.calculateVehicleSpeed(frm_100.get_accelerator(), frm_200.get_rpm());
    gb.selectGear(frm_100.get_accelerator(), frm_200.get_rpm());
    //fuel_class.CalculateFuel(frm_100, rpm, frm_300);
    //info = di.getDriverInfoMsg();
}

void TCM::Write(fr::frame_300 &frm_300) //remove frame 200 and change get vehicle speed behaviour
{
    std::cout << "Speed : " << (int)gb.getVehicleSpeed() << std::endl;
    frm_300.set_gearactual(gb.getGear());
    uint16_t speed = gb.getVehicleSpeed();
    VehicleSpeedFilter(speed);
    
    frm_300.set_speed(speed);
    frm_300.set_gearratio(gb.getGearRatio());
    //frm_300.set_gearactual(gb.??);
    frm_300.set_updatebit(1);
};

void TCM::VehicleSpeedFilter(uint16_t &speed){

    uint16_t sum = 0;
    vehiclespeedfilter.pop_back();
    vehiclespeedfilter.push_front(speed);

    for(auto i : vehiclespeedfilter) //sum elements
                    sum += i;

    speed = sum / vehiclespeedfilterSamples;
}
