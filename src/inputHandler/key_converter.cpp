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
    this->required_action = static_cast<UserReq>(key);
    
    return required_action;
}