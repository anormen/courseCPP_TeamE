#include "conversion.hpp"

Conversion::Conversion(){
    // Empty
}

void Conversion::AccPedUp(){
    int8_t acc = this->frm_100.get_accelerator() + 10;
    if(acc > 100)
        acc = 100;
    frm_100.set_accelerator(acc);
}
void Conversion::AccPedDown(){     
    int8_t acc = this->frm_100.get_accelerator() - 10; 
    if (acc < 0) 
        acc = 0;
    frm_100.set_accelerator(acc);
}
void Conversion::BrakePedalUp(){
    int8_t brk = this->frm_100.get_brake() + 10;
    if (brk > 100)
        brk = 100;
    frm_100.set_brake(brk);
}
void Conversion::BrakePedalDown(){
    int8_t brk = this->frm_100.get_brake() - 10;
    if (brk < 0)
        brk = 0;
    this->frm_100.set_brake(brk);
}
void Conversion::SetStartButton(){
    this->frm_100.set_startstop(fr::StartButtonSts::PRESSED);
}
void Conversion::ReleaseStartButton(){
    this->frm_100.set_startstop(fr::StartButtonSts::UNPRESSED);
}
void Conversion::GearLeverUp(){

    switch(this->frm_100.get_gearlever())
    {
        case fr::GearLeverPos::PARK:
            this->frm_100.set_gearlever(fr::GearLeverPos::REVERSE);
            break;
        case fr::GearLeverPos::REVERSE:
            this->frm_100.set_gearlever(fr::GearLeverPos::NEUTRAL);
            break;      
        case fr::GearLeverPos::NEUTRAL:
            this->frm_100.set_gearlever(fr::GearLeverPos::DRIVE);
            break;    
        case fr::GearLeverPos::DRIVE:
            this->frm_100.set_gearlever(fr::GearLeverPos::DRIVE);
            break;                       
        default:
            this->frm_100.set_gearlever(fr::GearLeverPos::PARK);
    }
}

void Conversion::GearLeverDown(){

    switch(this->frm_100.get_gearlever())
    {
        case fr::GearLeverPos::PARK:
            this->frm_100.set_gearlever(fr::GearLeverPos::PARK);
            break;
        case fr::GearLeverPos::REVERSE:
            this->frm_100.set_gearlever(fr::GearLeverPos::PARK);
            break;      
        case fr::GearLeverPos::NEUTRAL:
            this->frm_100.set_gearlever(fr::GearLeverPos::REVERSE);
            break;    
        case fr::GearLeverPos::DRIVE:
            this->frm_100.set_gearlever(fr::GearLeverPos::NEUTRAL);
            break;                       
        default:
            this->frm_100.set_gearlever(fr::GearLeverPos::PARK);
    }
}

void Conversion::SetSimulationMode(){

    switch(this->frm_100.get_mode())
    {
        case fr::SimulationMode::SLEEP:
            this->frm_100.set_mode(fr::SimulationMode::INACTIVE);
            break;
        case fr::SimulationMode::INACTIVE:
            this->frm_100.set_mode(fr::SimulationMode::ACTIVE);
            break;
        case fr::SimulationMode::ACTIVE:
            this->frm_100.set_mode(fr::SimulationMode::OFF);
            break;     
        default:
            this->frm_100.set_mode(fr::SimulationMode::SLEEP);          
    }
}

void  Conversion::fillFrame(can_frame &_frame, kc::UserReq _userReq){
   
    switch (_userReq){
        case kc::UserReq::SIMULATION_MODE: // m
            SetSimulationMode();
            break;      
        case  kc::UserReq::ACC_PED_UP: // Arrow UP
            AccPedUp();
            break;
        case  kc::UserReq::ACC_PED_DOWN: //Arrow Down
            AccPedDown();
            break;
        case kc::UserReq::STARTBUTTON: // s
            SetStartButton();
            break;
        case kc::UserReq::BRAKE_PED_UP: //->
            BrakePedalUp();
            break;
        case kc::UserReq::BRAKE_PED_DOWN: //<-
            BrakePedalDown();
            break;
        case kc::UserReq::GEARLEV_UP: //+
            GearLeverUp();
            break;
        case kc::UserReq::GEARLEV_DOWN: //-
            GearLeverDown();
            break;
        default:  
            ReleaseStartButton();   // NOT OK SOLUTION NEED IMPROVMENT      
    }
    //std::cout << "&data_to_send = " << &data_to_send << " &data_to_send+6 " << &data_to_send+6 << std::endl;
    frm_100.set_updatebit(1);
    memcpy(&_frame, frm_100.get_frame_ptr(), sizeof(_frame));
}

Conversion::~Conversion(){
    //empty
}