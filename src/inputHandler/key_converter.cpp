#include "key_converter.hpp"
#include "conversion.hpp"

UserReq readKeyboard()
{
    UserReq uReq;
    unsigned char key;
    std::cin >> key;

    auto action = intKeyToEnumAction.find(key);
    if (action == intKeyToEnumAction.end()) {
        std::cout << "Code: " << key << " not found" << std::endl; 
        uReq = UserReq::UNDEFINED;
    }
    else{
        std::cout << "Key: " << key << "Action: " << (int)action->second << std::endl;
        uReq = action->second;
    }

    std::cin.clear();
    return uReq;
}