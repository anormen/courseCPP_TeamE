#ifndef ECM_HPP
#define ECM_HPP

#include "../TCM/TCM.hpp"
#include "frames.hpp"

class ECM 
{
  public:
    ECM();
    ~ECM() = default;
    void CalculateRPM(int acc_ped, StartButtonSts startstop);
    int GetRPM();
  private:
    int RPM;
    //TCM tcm;
};

#endif //ECM_HPP