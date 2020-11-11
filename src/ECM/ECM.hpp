#ifndef ECM_HPP
#define ECM_HPP

#include "../TCM/TCM.hpp"
#include "frames.hpp"

class ECM 
{
  public:
    ECM();
    ~ECM() = default;
    void UpdateECM(int acc_ped, uint8_t startstop);
    void CalculateRPM(int acc_ped);
    int GetRPM();
  private:
    int RPM;
    bool eng_on;
    //TCM tcm;
};

#endif //ECM_HPP