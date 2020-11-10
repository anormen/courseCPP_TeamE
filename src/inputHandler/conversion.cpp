#include "conversion.hpp"

Conversion::Conversion(){

    fr100_to_send.accelerator= 0x0;
    fr100_to_send.startstop= (uint8_t)StartButtonSts::UNPRESSED;
    fr100_to_send.brake= 0x0;
    fr100_to_send.mode= (uint8_t)SimulationMode::SLEEP;
    fr100_to_send.gearlever= (uint8_t)GearLeverPos::PARK;
    fr100_to_send.updatebit = 0x1;
    fr100_to_send.res0 = 0x0;
    fr100_to_send.res1 = 0x0;  
    fr100_to_send.res2 = 0x0;   
    fr100_to_send.res3 = 0x0;       
}

void Conversion::AccPedUp(){
    fr100_to_send.accelerator = fr100_to_send.accelerator + 10;
    if (fr100_to_send.accelerator > 100) { 
        fr100_to_send.accelerator = 100;
    }
}
void Conversion::AccPedDown(){      
    if (fr100_to_send.accelerator >10) { 
        fr100_to_send.accelerator = fr100_to_send.accelerator - 10;
    }
    else {
        fr100_to_send.accelerator = 0;
    }
}
void Conversion::BrakePedalUp(){
    fr100_to_send.brake = fr100_to_send.brake + 10;
    if (fr100_to_send.brake > 100) { 
        fr100_to_send.brake = 100;
    }
}
void Conversion::BrakePedalDown(){
    if (fr100_to_send.brake <10) { 
        fr100_to_send.brake = fr100_to_send.brake - 10;
    }
    else {
        fr100_to_send.brake = 0;
    }
}
void Conversion::SetStartButton(){
        fr100_to_send.startstop = (uint8_t)StartButtonSts::PRESSED;
}
void Conversion::ReleaseStartButton(){
         fr100_to_send.startstop = (uint8_t)StartButtonSts::UNPRESSED;
}
void Conversion::GearLeverUp(){

        switch(fr100_to_send.gearlever)
        {
            case (uint8_t)GearLeverPos::PARK:
                fr100_to_send.gearlever = (uint8_t)GearLeverPos::REVERSE;
                break;
            case (uint8_t)GearLeverPos::REVERSE:
                fr100_to_send.gearlever = (uint8_t)GearLeverPos::NEUTRAL;
                break;      
            case (uint8_t)GearLeverPos::NEUTRAL:
                fr100_to_send.gearlever = (uint8_t)GearLeverPos::DRIVE;
                break;    
            case (uint8_t)GearLeverPos::DRIVE:
                fr100_to_send.gearlever = (uint8_t)GearLeverPos::DRIVE;
                break;                       
            default:
                fr100_to_send.gearlever = (uint8_t)GearLeverPos::PARK;
        }
}

void Conversion::GearLeverDown(){

        switch(fr100_to_send.gearlever)
        {
            case (uint8_t)GearLeverPos::PARK:
                fr100_to_send.gearlever = (uint8_t)GearLeverPos::PARK;
                break;
            case (uint8_t)GearLeverPos::REVERSE:
                fr100_to_send.gearlever = (uint8_t)GearLeverPos::PARK;
                break;      
            case (uint8_t)GearLeverPos::NEUTRAL:
                fr100_to_send.gearlever = (uint8_t)GearLeverPos::REVERSE;
                break;    
            case (uint8_t)GearLeverPos::DRIVE:
                fr100_to_send.gearlever = (uint8_t)GearLeverPos::NEUTRAL;
                break;                       
            default:
                fr100_to_send.gearlever = (uint8_t)GearLeverPos::PARK;
        }
}

void Conversion::SetSimulationMode(){

    switch(fr100_to_send.mode)
    {
        case (uint8_t)SimulationMode::SLEEP:
            fr100_to_send.mode=(uint8_t)SimulationMode::INACTIVE;
            break;
        case (uint8_t)SimulationMode::INACTIVE:
            fr100_to_send.mode=(uint8_t)SimulationMode::ACTIVE;
            break;
        case (uint8_t)SimulationMode::ACTIVE:
            fr100_to_send.mode=(uint8_t)SimulationMode::OFF;
            break;     
        default:
            fr100_to_send.mode=(uint8_t)SimulationMode::SLEEP;          
    }
}

void  Conversion::fillFrame(can_frame &_frame, UserReq _userReq){
   
    switch (_userReq){
        case UserReq::SIMULATION_MODE: // m
            SetSimulationMode();
            break;      
        case  UserReq::ACC_PED_UP: // Arrow UP
            AccPedUp();
            break;
        case  UserReq::ACC_PED_DOWN: //Arrow Down
            AccPedDown();
            break;
        case UserReq::STARTBUTTON: // s
            SetStartButton();
            break;
        case UserReq::BRAKE_PED_UP: //
            BrakePedalUp();
            break;
        case UserReq::BRAKE_PED_DOWN: //
            BrakePedalDown();
            break;
        case UserReq::GEARLEV_UP:
            GearLeverUp();
            break;
        case UserReq::GEARLEV_DOWN:
            GearLeverDown();
            break;
        default:  
            ReleaseStartButton();   // NOT OK SOLUTION NEED IMPROVMENT      
    }
    //std::cout << "&data_to_send = " << &data_to_send << " &data_to_send+6 " << &data_to_send+6 << std::endl;
    memcpy(&_frame,&fr100_to_send,16);
}

Conversion::~Conversion(){}