#ifndef CONVERSION_H
#define CONVERSION_H

#include <iostream>
#include "frames.hpp"
#include "key_converter.hpp"

namespace fr=frames;

bool exeCommand(fr::frame_100&, UserReq);
void AccPedUp(fr::frame_100&);
void AccPedDown(fr::frame_100&);
void BrakePedalUp(fr::frame_100&);
void BrakePedalDown(fr::frame_100&);
void GearLeverUp(fr::frame_100&);
void GearLeverDown(fr::frame_100&);    
void SetStartButton(fr::frame_100&);
void ReleaseStartButton(fr::frame_100&);
void SetSimulationMode(fr::frame_100&);  

const std::unordered_map<UserReq, std::function<void(fr::frame_100&)>> EnumActionToFunc
{
  { UserReq::SIMULATION_MODE, SetSimulationMode },
  { UserReq::STARTBUTTON, SetStartButton },
  { UserReq::GEARLEV_UP, GearLeverUp },
  { UserReq::GEARLEV_DOWN, GearLeverDown },
  { UserReq::ACC_PED_UP, AccPedUp },
  { UserReq::ACC_PED_DOWN, AccPedDown },
  { UserReq::BRAKE_PED_DOWN, BrakePedalDown },
  { UserReq::BRAKE_PED_UP, BrakePedalUp },
  { UserReq::UNDEFINED, ReleaseStartButton }  
};
#endif