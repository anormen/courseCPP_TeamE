#ifndef CONVERSION_H
#define CONVERSION_H

#include <iostream>
#include "can_class.hpp"
#include <linux/can.h>
#include <linux/can/raw.h>
#include "frames.hpp"
#include "key_converter.hpp"

namespace kc=key_conv;

class Conversion{

private:
   // Frame_data inputHandlerFrame;
    frame_100 frm_100;
    void AccPedUp();
    void AccPedDown();
    void BrakePedalUp();
    void BrakePedalDown();
    void GearLeverUp();
    void GearLeverDown();    
    void SetStartButton();
    void ReleaseStartButton();
    void SetSimulationMode();    
    
public:
    Conversion();
    void fillFrame(can_frame &_frame, kc::UserReq _userReq);
    SimulationMode GetSimulationMode() { return this->frm_100.get_mode(); };     
   ~Conversion();
};

#endif