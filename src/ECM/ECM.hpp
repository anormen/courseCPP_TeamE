#ifndef ECM_HPP
#define ECM_HPP

#include "frames.hpp"
#include "calcFuel.hpp"
#include "calcRPM.hpp"
#include "driverInfo.hpp"

namespace fr = frames;

class ECM
{
public:
    ECM();
    void Update();
    void Write(fr::frameVector data_vec);
    void Read(fr::frameVector data_vec);

private:
    uint16_t rpm, veh_speed;
    uint8_t counter, temp, acc, gear_ratio, updatebit, brake;
    bool eng_on;
    fr::StartButtonSts startstop;
    fr::SimulationMode mode;
    fr::GearLeverPos gear_lever;
    calcRPM rpm_class;
    calcFuel fuel_class;
    driverInfo di; // should probably be a method
    void CalculateTemp();

    friend class driverInfo;
};

#endif //ECM_HPP