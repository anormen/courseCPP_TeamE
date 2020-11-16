#ifndef ECM_HPP
#define ECM_HPP

#include "../TCM/TCM.hpp"
#include "frames.hpp"
#include "calcFuel.hpp"
#include "calcRPM.hpp"
#include "driverInfo.hpp"

const int max_rpm=8000;
const int shift_rpm=3200; // REMOVE LATER


class ECM
{
  public:
    void Update(frame_100 &frm_100, frame_300 &frm_300){


        rpm = rpm_class.CalculateRPM(frm_100.get_accelerator(), frm_100.get_startstop(), infoMsg);
        fuel_class.CalculateFuel(frm_100, rpm, frm_300);
        di.update(frm_100, rpm, infoMsg);
        //info = di.getDriverInfoMsg();
    }
    void Write(frame_200 &frm_200){
        frm_200.set_rpm(rpm);
        fuel_class.set_Fuel(frm_200);
        frm_200.set_driverinfor(infoMsg);
    };
  private:
    uint16_t rpm;
    DriverInformation infoMsg;
    calcRPM rpm_class;
    calcFuel fuel_class;
    driverInfo di;
};

#endif //ECM_HPP