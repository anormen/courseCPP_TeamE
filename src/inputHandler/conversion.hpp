#ifndef CONVERSION_H
#define CONVERSION_H

#include <iostream>
#include "frames.hpp"
#include "key_converter.hpp"

namespace kc=key_conv;
namespace fr=frames;

class Conversion{

private:
    void AccPedUp(fr::frame_100 &frm_100);
    void AccPedDown(fr::frame_100 &frm_100);
    void BrakePedalUp(fr::frame_100 &frm_100);
    void BrakePedalDown(fr::frame_100 &frm_100);
    void GearLeverUp(fr::frame_100 &frm_100);
    void GearLeverDown(fr::frame_100 &frm_100);    
    void SetStartButton(fr::frame_100 &frm_100);
    void ReleaseStartButton(fr::frame_100 &frm_100);
    void SetSimulationMode(fr::frame_100 &frm_100);    
    
public:
    Conversion();
    void fillFrame(fr::frame_100 &frm_100, kc::UserReq _userReq);
   ~Conversion();
};

#endif