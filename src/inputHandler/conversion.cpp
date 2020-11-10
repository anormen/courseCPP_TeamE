
#include "conversion.hpp"

Conversion::Conversion(){

    
    //memset(&fr100_to_send,0,sizeof(fr100_to_send));
    fr100_to_send.accelerator=0;
    fr100_to_send.startstop=(uint8_t)StartButtonSts::UNPRESSED;
    fr100_to_send.brake=0;
    fr100_to_send.mode=(uint8_t)SimulationMode::SLEEP;

    
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
    fr100_to_send.brake = 100;
}
void Conversion::BrakePedalDown(){
    fr100_to_send.brake = 0; 
}
void Conversion::SetStartButton(){
        fr100_to_send.startstop = (uint8_t)StartButtonSts::PRESSED;
}
void Conversion::ReleaseStartButton(){
         fr100_to_send.startstop = (uint8_t)StartButtonSts::UNPRESSED;
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
    case UserReq::BRAKE_PED_DOWN: //
        BrakePedalDown();
    default :  
        ReleaseStartButton();   // NOT OK SOLUTION NEED IMPROVMENT      
    }


    //std::cout << "&data_to_send = " << &data_to_send << " &data_to_send+6 " << &data_to_send+6 << std::endl;
    memcpy(&_frame,&fr100_to_send,16);
}

Conversion::~Conversion(){}
