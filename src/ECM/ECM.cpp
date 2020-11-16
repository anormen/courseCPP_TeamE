#include "ECM.hpp"

void ECM::Update(frame_100 &frm_100, frame_300 &frm_300)
{

    di.update(frm_100, rpm, infoMsg);
    rpm = rpm_class.CalculateRPM(frm_100.get_accelerator(), frm_100.get_startstop(), infoMsg);
    fuel_class.CalculateFuel(frm_100, rpm, frm_300);

    //info = di.getDriverInfoMsg();
}

void ECM::Write(frame_200 &frm_200)
{
    frm_200.set_rpm(rpm);
    frm_200.set_fuelavg(fuel_class.getFuelAvg());
    frm_200.set_fuelinst(fuel_class.getFuelInst());
    frm_200.set_driverinfor(infoMsg);
};