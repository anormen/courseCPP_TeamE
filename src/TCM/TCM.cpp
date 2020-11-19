#include "TCM.hpp"

void TCM::Update(fr::frame_100 &frm_100, fr::frame_200 &frm_200)
{
    
    gb.selectGear(frm_100.get_accelerator(), frm_200.get_rpm());
    //do something here 
    //fuel_class.CalculateFuel(frm_100, rpm, frm_300);
    //info = di.getDriverInfoMsg();
}

void TCM::Write(fr::frame_100 &frm_100, fr::frame_200 &frm_200, fr::frame_300 &frm_300) //remove frame 200 and change get vehicle speed behaviour
{
    std::cout << "Speed : " << (int)gb.getVehicleSpeed(frm_100.get_accelerator(),frm_200.get_rpm()) << std::endl;
    frm_300.set_gearactual(gb.getGear());
    frm_300.set_speed(gb.getVehicleSpeed(frm_100.get_accelerator(), frm_200.get_rpm()));
    frm_300.set_gearratio(gb.getGearRatio(frm_200.get_rpm()));
    //frm_300.set_gearactual(gb.??);
    frm_300.set_updatebit(1);
};