#include "key_converter.hpp"

namespace key_Converter { 

keyConverter::keyConverter()
{
    // Init ncurses key input
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

UserReq keyConverter::readKeyInputReq()
{
    UserReq uAction;
    int key = getch();
 
    auto action = intKeyToEnumAction.find(key);
    if (action == intKeyToEnumAction.end()) {
        std::cout << "Code: " << key << " not found\n\r"; 
        uAction = UserReq::UNDEFINED;
    }
    else {
        std::cout << "Key: " << key << " Action: " << (int)action->second << "\n\r";
        uAction = action->second;
    }
    return uAction;
}

} // namespace key_converter