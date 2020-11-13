#ifndef KEY_CONVERTER_HPP
#define KEY_CONVERTER_HPP

#include <iostream>
#include <curses.h>

enum class UserReq { SIMULATION_MODE, STARTBUTTON, ACC_PED_UP, ACC_PED_DOWN, BRAKE_PED_UP, BRAKE_PED_DOWN, GEARLEV_UP, GEARLEV_DOWN, UNDEFINED };

const struct req_key {
    int simulation_mode = 109; // m
    int startbutton = 115; // s
    int acc_ped_up = 259; // arrow up
    int acc_ped_down = 258; // arrow down
    int brake_ped_up = 261; // arrow right
    int brake_ped_down = 260; // arrow left
    int gearlev_up = 43; // +
    int gearlev_down = 45; // -
} key_req_map;

class keyConverter{
  public:
    keyConverter();
    UserReq readInputReq();
  private:
    UserReq required_action;
    int key;
};

#endif //KEY_CONVERTER_HPP