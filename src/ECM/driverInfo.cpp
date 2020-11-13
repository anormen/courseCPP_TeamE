#include "driverInfo.hpp"

void driverInfo::update(const fr100 &dataread, fr200 &datawrite){
    //local variables
    uint8_t gearleverpos = gearLeverPos(dataread);
    uint8_t startbutton = startButtonStatus(dataread);
    uint8_t brake = brakePosition(dataread);
    uint16_t rpm = rpmValue(datawrite);  
    uint8_t mode = modeStatus(dataread);
   
    if(startbutton == (uint8_t)StartButtonSts::PRESSED && mode == (uint8_t)SimulationMode::ACTIVE){ //handler active
        if (rpm > 0) //running
            infoMsg = DriverInformation::NOT_IN_P_IN_D;
        else if(brake == 0) //not pressed
            infoMsg = DriverInformation::NO_BRAKE;
        else if (gearleverpos != (uint8_t)GearLeverPos::PARK)
            infoMsg = DriverInformation::NOT_IN_P;
        else 
            infoMsg = DriverInformation::NO_MSG;  //ok to start stop engine

        if(infoMsg != DriverInformation::NO_MSG){ //start new message timeout
            startTime = std::chrono::steady_clock::now();
        }
    }
    
    uint16_t messageTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-startTime).count();
    if(messageTime >= messageDuration || mode != (uint8_t)SimulationMode::ACTIVE) //message timeout or vehicle turned off 
        infoMsg = DriverInformation::NO_MSG;

    //debug message
    //std::cout << messages.at((uint8_t)infoMsg) << " T: "<< messageTime << " S: " << (int)startbutton << " BR: " 
    //   << (int)brake << " Gear: " << gears.at((uint8_t)gearleverpos) << " rpm: " << (int)rpm << std::endl; 
    updateInfoMsg(datawrite);
};

uint8_t driverInfo::gearLeverPos(const fr100 &dataread){
    //need to fetch value from can for gearlever fr100 uint8_t gearlever:4;
    return dataread.gearlever;
};
        
uint8_t driverInfo::modeStatus(const fr100 &dataread){
    //need to fetch value from can for Simulation mode fr100 uint8_t mode:2;
    return dataread.mode;
};
        
uint8_t driverInfo::startButtonStatus(const fr100 &dataread){
    //need to fetch value from can for start button fr100 uint8_t startstop:1;
    return dataread.startstop;
};
uint8_t driverInfo::brakePosition(const fr100 &dataread){
    //need to fetch value from can for brake position fr100 uint8_t brake:8;
    return dataread.brake;
};
uint16_t driverInfo::rpmValue(fr200 &datawrite){
    //need to fetch value from internal ECM for RPM
    return datawrite.rpm;
};

void driverInfo::updateInfoMsg(fr200 &datawrite){
    //need to put value to can frame 200 uint8_t driverinfo:4;
    datawrite.driverinfo = (uint8_t)infoMsg;
    return;
};