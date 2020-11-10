#include "key_converter.hpp"

keyConverter::keyConverter()
{
    // Init ncurses key input
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    this->required_action = UserReq::UNDEFINED;
}

UserReq keyConverter::readInputReq()
{
    this->key = getch();
    //this->required_action = static_cast<UserReq>(key);

    // Maybe define map somewhere
    //std::map<int,UserReq> keyconv_map;
    //keyconv_map.insert(std::pair<int,UserReq>(259,UserReq::ACC_PED_UP));
    //keyconv_map.insert(std::pair<int,UserReq>(258,UserReq::ACC_PED_DOWN));


    // Should perhaps define key->req pairs/conversion somewhere else, not hardcode i .cpp file
    if(key==259) // arrow up
        required_action=UserReq::ACC_PED_UP;
    else if (key==258) // arrow down
        required_action=UserReq::ACC_PED_DOWN;
    else if (key==115) // s
        required_action=UserReq::STARTBUTTON;
    else if (key==109) // m
        required_action=UserReq::SIMULATION_MODE;
    else if (key==261) // arrow right
        required_action=UserReq::BRAKE_PED_UP;
    else if (key==260) // arrow left
        required_action=UserReq::BRAKE_PED_DOWN;
    else if(key==43) // +
        required_action=UserReq::GEARLEV_UP;
    else if(key==45) // -
        required_action=UserReq::GEARLEV_DOWN;
    else
        required_action=UserReq::UNDEFINED;
    

    return required_action;
}