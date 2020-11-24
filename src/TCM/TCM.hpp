#ifndef TCM_HPP
#define TCM_HPP

#include "frames.hpp"
#include "gearbox.hpp"
#include <deque>

namespace fr=frames;

class TCM 
{
  public:
    TCM();
    ~TCM() = default;
    void Update(fr::frame_100 &frm_100, fr::frame_200 &frm_200);
    uint16_t VehicleSpeedFilter(const uint16_t &speed);
    void Write(fr::frame_300 &frm_300);
  private:
    Gearbox gb;
    std::deque<uint16_t> vehiclespeedfilter;
    float vehiclespeedfilterSamples = 20.0;
};

#endif //TCM_HPP