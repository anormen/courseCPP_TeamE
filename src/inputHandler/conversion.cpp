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
    this->frm_100.set_startstop(StartButtonSts::PRESSED);
}
void Conversion::ReleaseStartButton(){
    this->frm_100.set_startstop(StartButtonSts::UNPRESSED);
}
void Conversion::GearLeverUp(){

    switch(this->frm_100.get_gearlever())
    {
        case GearLeverPos::PARK:
            this->frm_100.set_gearlever(GearLeverPos::REVERSE);
            break;
        case GearLeverPos::REVERSE:
            this->frm_100.set_gearlever(GearLeverPos::NEUTRAL);
            break;      
        case GearLeverPos::NEUTRAL:
            this->frm_100.set_gearlever(GearLeverPos::DRIVE);
            break;    
        case GearLeverPos::DRIVE:
            this->frm_100.set_gearlever(GearLeverPos::DRIVE);
            break;                       
        default:
            this->frm_100.set_gearlever(GearLeverPos::PARK);
    }
}

void Conversion::GearLeverDown(){

    switch(this->frm_100.get_gearlever())
    {
        case GearLeverPos::PARK:
            this->frm_100.set_gearlever(GearLeverPos::PARK);
            break;
        case GearLeverPos::REVERSE:
            this->frm_100.set_gearlever(GearLeverPos::PARK);
            break;      
        case GearLeverPos::NEUTRAL:
            this->frm_100.set_gearlever(GearLeverPos::REVERSE);
            break;    
        case GearLeverPos::DRIVE:
            this->frm_100.set_gearlever(GearLeverPos::NEUTRAL);
            break;                       
        default:
            this->frm_100.set_gearlever(GearLeverPos::PARK);
    }
}

void Conversion::SetSimulationMode(){

    switch(this->frm_100.get_mode())
    {
        case SimulationMode::SLEEP:
            this->frm_100.set_mode(SimulationMode::INACTIVE);
            break;
        case SimulationMode::INACTIVE:
            this->frm_100.set_mode(SimulationMode::ACTIVE);
            break;
        case SimulationMode::ACTIVE:
            this->frm_100.set_mode(SimulationMode::OFF);
            break;     
        default:
            this->frm_100.set_mode(SimulationMode::SLEEP);          
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