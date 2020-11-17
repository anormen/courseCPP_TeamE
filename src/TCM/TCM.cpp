#include "TCM.hpp"

void TCM::Update(frame_100 &frm_100, frame_200 &frm_200)
{
    //do something here 
    //fuel_class.CalculateFuel(frm_100, rpm, frm_300);
    //info = di.getDriverInfoMsg();
}

void TCM::Write(frame_200 &frm_200, frame_300 &frm_300) //remove frame 200 and change get evhicle speed behaviour
{
    std::cout << "Speed : " << (int)gb.getVehicleSpeed(frm_200.get_rpm()) << std::endl;
    frm_300.set_speed(gb.getVehicleSpeed(frm_200.get_rpm()));
    //frm_300.set_gearactual(gb.??);
    frm_300.set_updatebit(1);
};