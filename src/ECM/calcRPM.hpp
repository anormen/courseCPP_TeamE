#ifndef CALCRPM_HPP
#define CLACRPM_HPP

#include<iostream>
#include "frames.hpp"

class calcRPM {
  public:
    uint16_t CalculateRPM(int acc_ped, StartButtonSts startstop, DriverInformation info);
  private:
    uint16_t rpm;
    bool eng_on;
    const int response_time=1000; // ms
    int acc_inc_delta;
    int acc_ped_stored;
    bool increasing_rpm;
    bool decreasing_rpm;
    int gear; // delete later
    int target_rpm;
};

#endif // CALCRPM_HPP