#include "key_converter.hpp"

namespace kc=key_conv;

kc::keyConverter::keyConverter()
{
    // Init ncurses key input
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    this->required_action = UserReq::UNDEFINED;
}

kc::UserReq kc::keyConverter::readInputReq()
{
    this->key = getch();

    if(key==key_req_map.acc_ped_up) 
        required_action=UserReq::ACC_PED_UP;
    else if (key==key_req_map.acc_ped_down) 
        required_action=UserReq::ACC_PED_DOWN;
    else if (key==key_req_map.startbutton) 
        required_action=UserReq::STARTBUTTON;
    else if (key==key_req_map.simulation_mode) 
        required_action=UserReq::SIMULATION_MODE;
    else if (key==key_req_map.brake_ped_up) 
        required_action=UserReq::BRAKE_PED_UP;
    else if (key==key_req_map.brake_ped_down) 
        required_action=UserReq::BRAKE_PED_DOWN;
    else if(key==key_req_map.gearlev_up) 
        required_action=UserReq::GEARLEV_UP;
    else if(key==key_req_map.gearlev_down) 
        required_action=UserReq::GEARLEV_DOWN;
    else
        required_action=UserReq::UNDEFINED;
    
    return required_action;
}