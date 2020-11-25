#ifndef CONVERSION_H
#define CONVERSION_H

#include <iostream>
#include "frames.hpp"
#include "key_converter.hpp"
#include <unordered_map>
#include <functional>

namespace kc = key_Converter;
namespace fr=frames;
//key handler functions
bool exeRequest(fr::frame_100&, kc::UserReq);
void AccPedUp(fr::frame_100&);
void AccPedDown(fr::frame_100&);
void BrakePedalUp(fr::frame_100&);
void BrakePedalDown(fr::frame_100&);
void GearLeverUp(fr::frame_100&);
void GearLeverDown(fr::frame_100&);    
void SetStartButton(fr::frame_100&);
void ReleaseStartButton(fr::frame_100&);
void SetSimulationMode(fr::frame_100&);
  
//action to function mapping
const std::unordered_map<kc::UserReq, std::function<void(fr::frame_100&)>> enumActionToFunc
{
  { kc::UserReq::SIMULATION_MODE, SetSimulationMode },
  { kc::UserReq::STARTBUTTON, SetStartButton },
  { kc::UserReq::GEARLEV_UP, GearLeverUp },
  { kc::UserReq::GEARLEV_DOWN, GearLeverDown },
  { kc::UserReq::ACC_PED_UP, AccPedUp },
  { kc::UserReq::ACC_PED_DOWN, AccPedDown },
  { kc::UserReq::BRAKE_PED_DOWN, BrakePedalDown },
  { kc::UserReq::BRAKE_PED_UP, BrakePedalUp },
  { kc::UserReq::UNDEFINED, ReleaseStartButton }  
};

#endif