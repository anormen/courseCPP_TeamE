#include "key_converter.hpp"
#include "conversion.hpp"



UserReq readKeyboard()
{
    std::unordered_map<unsigned char, UserReq> intKeyToEnumAction(
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
    });


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