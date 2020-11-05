#ifndef TCM_HPP
#define TCM_HPP

class TCM
{
  public:
    void CalculateGear(int &RPM);
    int GetGear();
  private:
    int gear;
};

#endif //TCM_HPP