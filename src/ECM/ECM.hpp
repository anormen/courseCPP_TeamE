#ifndef ECM_HPP
#define ECM_HPP

class ECM 
{
  public:
    ECM();
    ~ECM() = default;
    void CalculateRPM(int acc_ped);
    int GetRPM();
  private:
    int RPM;
};

#endif //ECM_HPP