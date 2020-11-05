#ifndef TCM_HPP
#define TCM_HPP

#include<iostream>

class TCM
{
  public:
    unsigned int CalculateGear(unsigned int RPM);
    int GetGear();
  private:
    int gear;
};

#endif //TCM_HPP