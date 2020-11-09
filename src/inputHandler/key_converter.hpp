#ifndef KEY_CONVERTER_HPP
#define KEY_CONVERTER_HPP

#include <iostream>
#include <curses.h>
#include <map> 

enum class UserReq { SIMULATION_MODE, STARTBUTTON, ACC_PED_UP, ACC_PED_DOWN, BRAKE_PED_UP, BRAKE_PED_DOWN, GEARLEV_UP, GEARLEV_DOWN, UNDEFINED };

class keyConverter{
  public:
    keyConverter();
    UserReq readInputReq();
  private:
    UserReq required_action;
    //void convertKey();
    int key;
};


#endif //KEY_CONVERTER_HPP