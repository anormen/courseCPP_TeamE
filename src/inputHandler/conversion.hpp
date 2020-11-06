#ifndef CONVERSION_H
#define CONVERSION_H

#include <iostream>
#include "inputHandlerFrame.h"
#include "can_class.h"
#include <linux/can.h>
#include <linux/can/raw.h>
#include "frame.hpp"

enum class UserReq { SIMULATION_MODE, STARTBUTTON, ACC_PED_UP, ACC_PED_DOWN, BRAKE_PED_UP, BRAKE_PED_DOWN, GEARLEV_UP, GEARLEV_DOWN, UNDEFINED };

class Conversion{

private:

   // Frame_data inputHandlerFrame;

    void AccPedUp();
    void AccPedDown();
    void BrakePedalUp();
    void BrakePedDown();
    void SetStartButton();
    void ReleaseStartButton();
    void SetSimulationMode();
    
public:
    Conversion();
    void getFrame(can_frame &_frame);
    void SetKey(int _key);
   ~Conversion();
};

#endif