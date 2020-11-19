#ifndef CALCRPM_HPP
#define CLACRPM_HPP

#include<iostream>

class calcRPM {
  public:
    calcRPM();
    uint16_t CalculateRPM(int acc_ped, int _gearRatio, bool eng_on);
  private:
    uint16_t rpm;
    int oldGearratio = 10;
    bool eng_on;
};

#endif // CALCRPM_HPP