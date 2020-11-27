#ifndef TCM_HPP
#define TCM_HPP

#include "frames.hpp"
#include "gearbox.hpp"
#include <deque>
#include <numeric>

namespace fr = frames;

class TCM
{
public:
    TCM();
    void Read(std::vector<fr::base_frame *> read_vec);
    void Update();
    void Write(std::vector<fr::base_frame *> write_vec);
    uint16_t VehicleSpeedFilter(const uint16_t &speed);
    ~TCM() = default;

private:
    uint8_t acc, updatebit;
    uint16_t rpm;
    fr::GearLeverPos gear_lever;
    Gearbox gb;
    std::deque<uint16_t> vehiclespeedfilter;
    float vehiclespeedfilterSamples = 20.0;
};

#endif //TCM_HPP