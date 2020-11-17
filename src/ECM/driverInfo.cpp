#include "driverInfo.hpp"

//void driverInfo::update(frame_100 &fr100, frame_200 &fr200){
void driverInfo::update(frame_100 &fr100, uint16_t &rpm, DriverInformation &infoMsg){
    //local variables
    GearLeverPos gearleverpos = fr100.get_gearlever();
    StartButtonSts startbutton = fr100.get_startstop();
    uint8_t brake = fr100.get_brake();
    //uint16_t rpm = fr200.get_rpm();  
    SimulationMode mode = fr100.get_mode();
    //DriverInformation infoMsg = fr200.get_driverinfo();
   
    if(startbutton == StartButtonSts::PRESSED && mode == SimulationMode::ACTIVE){ //handler active
        if (rpm > 0 && gearleverpos != GearLeverPos::PARK) //running
            infoMsg = DriverInformation::NOT_IN_P_IN_D;
        else if(brake == 0) //not pressed
            infoMsg = DriverInformation::NO_BRAKE;
        else if (gearleverpos != GearLeverPos::PARK)
            infoMsg = DriverInformation::NOT_IN_P;
        else 
            infoMsg = DriverInformation::NO_MSG;  //ok to start stop engine

        if(infoMsg != DriverInformation::NO_MSG){ //start new message timeout
            startTime = std::chrono::steady_clock::now();
        }
    }
    
    uint16_t messageTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-startTime).count();
    if(messageTime >= messageDuration || mode != SimulationMode::ACTIVE) //message timeout or vehicle turned off 
        infoMsg = DriverInformation::NO_MSG;

    //debug message
    //std::cout << messages.at((uint8_t)infoMsg) << " T: "<< messageTime << " S: " << (int)startbutton << " BR: " 
    //  << (int)brake << " Gear: " << gears.at((uint8_t)gearleverpos) << " rpm: " << (int)rpm << std::endl; 
    //fr200.set_driverinfor(infoMsg);

};