#include "driverInfo.hpp"

void driverInfo::update(fr::frame_100 &fr100, const uint16_t &rpm, fr::DriverInformation &infoMsg){
    //local variables
    fr::GearLeverPos gearleverpos = fr100.get_gearlever();
    fr::StartButtonSts startbutton = fr100.get_startstop();
    uint8_t brake = fr100.get_brake();
    fr::SimulationMode mode = fr100.get_mode();
  
    if(startbutton == fr::StartButtonSts::PRESSED){ //handler active
        if(mode == fr::SimulationMode::INACTIVE)
            infoMsg = fr::DriverInformation::NO_KEY;
        else if (rpm > 0 && gearleverpos != fr::GearLeverPos::PARK) //running
            infoMsg = fr::DriverInformation::NOT_IN_P_IN_D;
        else if(brake == 0) //not pressed
            infoMsg = fr::DriverInformation::NO_BRAKE;
        else if (gearleverpos != fr::GearLeverPos::PARK)
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
};