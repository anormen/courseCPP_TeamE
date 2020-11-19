#ifndef ECM_HPP
#define ECM_HPP

#include "../TCM/TCM.hpp"
#include "../TCM/gearbox.hpp"
#include "frames.hpp"
#include "calcFuel.hpp"
#include "calcRPM.hpp"
#include "driverInfo.hpp"

namespace fr=frames;

class ECM
{
  public:
    ECM();
    void Update(fr::frame_100 &frm_100, fr::frame_300 &frm_300);
    void Write(fr::frame_200 &frm_200);

  private:
    uint16_t rpm;
    uint8_t temp, counter;
    fr::DriverInformation infoMsg;
    calcRPM rpm_class;
    calcFuel fuel_class;
    driverInfo di;
    bool eng_on;
    void CalculateTemp();
    fr::StartButtonSts stored_button;
};

#endif //ECM_HPP