#ifndef TCM_HPP
#define TCM_HPP

#include "frames.hpp"
#include "gearbox.hpp"
#include <deque>
#include <numeric>

namespace fr=frames;

class TCM 
{
  public:
    TCM();
    void Update(fr::frame_100 &frm_100, fr::frame_200 &frm_200);
    uint16_t VehicleSpeedFilter(const uint16_t &speed);
    void Write(fr::frame_300 &frm_300);
    ~TCM() = default;    
  private:
    Gearbox gb;
    std::deque<uint16_t> vehiclespeedfilter;
    float vehiclespeedfilterSamples = 20.0;
};

#endif //TCM_HPP