#ifndef KEY_CONVERTER_HPP
#define KEY_CONVERTER_HPP

#include <iostream>
#include <curses.h>
#include <unordered_map>
#include <functional>

namespace key_Converter {  

enum class UserReq { SIMULATION_MODE, STARTBUTTON, ACC_PED_UP, ACC_PED_DOWN, BRAKE_PED_UP, BRAKE_PED_DOWN, GEARLEV_UP, GEARLEV_DOWN, UNDEFINED };

class keyConverter{
  public:
    keyConverter();
    UserReq readKeyInputReq();
    ~keyConverter() { endwin(); };
  private:
};

const std::unordered_map<int, UserReq> intKeyToEnumAction
{
  { 109 , UserReq::SIMULATION_MODE }, //m
  { 115 , UserReq::STARTBUTTON }, //s
  {  43 , UserReq::GEARLEV_UP }, //+
  {  45 , UserReq::GEARLEV_DOWN }, //-
  { 259 , UserReq::ACC_PED_UP }, // arrow up
  { 258 , UserReq::ACC_PED_DOWN }, //arrow down
  { 260 , UserReq::BRAKE_PED_DOWN }, //arrow left
  { 261 , UserReq::BRAKE_PED_UP } //arraow right  
};

} //namespace key_conv

#endif //KEY_CONVERTER_HPP