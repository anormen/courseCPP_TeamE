#ifndef ECM_HPP
#define ECM_HPP

#include "../TCM/TCM.hpp"
#include "frames.hpp"

const int max_rpm=8000;
const int shift_rpm=3200; // REMOVE LATER

class ECM 
{
  public:
    ECM();
    ~ECM() = default;
    void UpdateECM(int acc_ped, StartButtonSts startstop);
    void CalculateRPM(int acc_ped);
    int GetRPM();
  private:
    int RPM;
    bool eng_on;
    const int response_time=1000; // ms
    int acc_inc_delta;
    int acc_ped_stored;
    bool increasing_rpm;
    bool decreasing_rpm;
    int gear; // delete later
    int target_rpm;
    //TCM tcm;
};

#endif //ECM_HPP