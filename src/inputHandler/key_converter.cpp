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

    std::cout << "\033c\033[0;32m" ; 
    std::cout << "---------------------------------\n\r";      
    std::cout << "Press 'm' to change mode\n\r";
    std::cout << "Press 's' to start engine\n\r"; 
    std::cout << "Press '+'/'-' to change gear PRND\n\r";   
    std::cout << "Press 'left'/'right' to brake\n\r";    
    std::cout << "Press 'up'/'down' to accelerate\n\r";
    std::cout << "---------------------------------\n\r";    

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