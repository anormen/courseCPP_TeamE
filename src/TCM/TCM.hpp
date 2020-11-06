#ifndef TCM_HPP
#define TCM_HPP

#include<iostream>

class TCM
{
  public:
    //TCM(){};
    void CalculateGear(int &RPM);
    int GetGear();
  private:
    int gear;
};

#endif //TCM_HPP