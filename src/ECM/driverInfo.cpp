#include "driverInfo.hpp"

fr::DriverInformation driverInfo::update(const fr::StartButtonSts &ss, const fr::SimulationMode &mode, const uint16_t &rpm, const uint8_t &brake, const fr::GearLeverPos &gear_lev){
    //local variables 

    if(ss == fr::StartButtonSts::PRESSED){ //handler active
        if(mode == fr::SimulationMode::INACTIVE)
            infoMsg = fr::DriverInformation::NO_KEY;
        else if (rpm > 0 && gear_lev != fr::GearLeverPos::PARK) //running
            infoMsg = fr::DriverInformation::NOT_IN_P_IN_D;
        else if (rpm == 0 && brake == 0) //not pressed
            infoMsg = fr::DriverInformation::NO_BRAKE;
        else if (gear_lev!= fr::GearLeverPos::PARK)
            infoMsg = fr::DriverInformation::NOT_IN_P;
        else 
            infoMsg = fr::DriverInformation::NO_MSG;  //ok to start stop engine

        if(infoMsg != fr::DriverInformation::NO_MSG){ //start new message timeout
            startTime = std::chrono::steady_clock::now();
        }
    }
    uint16_t messageTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-startTime).count();
    if(messageTime >= messageDuration || mode == fr::SimulationMode::SLEEP) //message timeout or vehicle turned off 
        infoMsg = fr::DriverInformation::NO_MSG;
    //debug message
    //std::cout << messages.at((uint8_t)infoMsg) << " T: "<< messageTime << " S: " << (int)startbutton << " BR: " 
    //  << (int)brake << " Gear: " << gears.at((uint8_t)gearleverpos) << " rpm: " << (int)rpm << std::endl; 
    return infoMsg;
}