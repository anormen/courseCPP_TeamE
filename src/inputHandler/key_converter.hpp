#ifndef KEY_CONVERTER_HPP
#define KEY_CONVERTER_HPP

#include <iostream>
#include <curses.h>
#include <unordered_map>
#include <functional>

enum class UserReq : uint8_t { SIMULATION_MODE, STARTBUTTON, ACC_PED_UP, ACC_PED_DOWN, BRAKE_PED_UP, BRAKE_PED_DOWN, GEARLEV_UP, GEARLEV_DOWN, UNDEFINED };
UserReq readKeyboard();
/*
    int simulation_mode = 109; // m
    int startbutton = 115; // s
    int acc_ped_up = 259; // arrow up
    int acc_ped_down = 258; // arrow down
    int brake_ped_up = 261; // arrow right
    int brake_ped_down = 260; // arrow left
    int gearlev_up = 43; // +
    int gearlev_down = 45; // -
*/

const std::unordered_map<unsigned char, UserReq> intKeyToEnumAction
{
  { 'm', UserReq::SIMULATION_MODE },
  { 's', UserReq::STARTBUTTON },
  { '+', UserReq::GEARLEV_UP },
  { '-', UserReq::GEARLEV_DOWN },
  { 'a', UserReq::ACC_PED_UP },
  { 'z', UserReq::ACC_PED_DOWN },
  { 'c', UserReq::BRAKE_PED_DOWN },
  { 'd', UserReq::BRAKE_PED_UP } ,   
  { ' ', UserReq::UNDEFINED }   
};

#endif //KEY_CONVERTER_HPP