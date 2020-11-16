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
    void Update(frame_100 &frm_100, frame_300 &frm_300);
    void Write(frame_200 &frm_200);
  private:
    uint16_t rpm;
    DriverInformation infoMsg;
    calcRPM rpm_class;
    calcFuel fuel_class;
    driverInfo di;
};

#endif //ECM_HPP