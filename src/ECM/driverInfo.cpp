#include "driverInfo.hpp"

void driverInfo::update(){
    //local variables
    uint8_t gearleverpos = gearLeverPos();
    uint8_t startbutton = startButtonStatus();
    uint8_t brake = brakePosition();
    uint16_t rpm = rpmValue();  
    uint8_t mode = modeStatus();
   
    if(startButtonStatus() == (uint8_t)StartButtonSts::PRESSED && modeStatus() == (uint8_t)SimulationMode::ACTIVE){ //handler active
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
    
    messageTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-startTime).count();
    if(messageTime >= timeoutT || mode != (uint8_t)SimulationMode::ACTIVE) //message timeout or vehicle turned off 
        infoMsg = DriverInformation::NO_MSG;

    //debug message
    //std::cout << messages.at((uint8_t)infoMsg) << " T: "<< messageTime << " S: " << (int)startbutton << " BR: " 
    //   << (int)brake << " Gear: " << gears.at((uint8_t)gearleverpos) << " rpm: " << (int)rpm << std::endl; 
};

uint8_t driverInfo::gearLeverPos(){
    //need to fetch value from can for gearlever fr100 uint8_t gearlever:4;
    return rand()%6;
};
        
uint8_t driverInfo::modeStatus(){
    //need to fetch value from can for Simulation mode fr100 uint8_t mode:2;
    return 2;
};
        
uint8_t driverInfo::startButtonStatus(){
    //need to fetch value from can for start button fr100 uint8_t startstop:1;
    return rand()%6;
};
uint8_t driverInfo::brakePosition(){
    //need to fetch value from can for brake position fr100 uint8_t brake:8;
    return rand()%6;
};
uint16_t driverInfo::rpmValue(){
    //need to fetch value from internal ECM for RPM
    return rand()%6;
};

void driverInfo::updateInfoMsg(){
    //need to put value to can frame 200 uint8_t driverinfo:4;
    return;
};