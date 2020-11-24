#include "conversion.hpp"

Conversion::Conversion(){
    // Empty
}

void Conversion::AccPedUp(fr::frame_100 &frm_100){
    int8_t acc = frm_100.get_accelerator() + 10;
    if(acc > 100)
        acc = 100;
    frm_100.set_accelerator(acc);
}
void Conversion::AccPedDown(fr::frame_100 &frm_100){     
    int8_t acc = frm_100.get_accelerator() - 10; 
    if (acc < 0) 
        acc = 0;
    frm_100.set_accelerator(acc);
}
void Conversion::BrakePedalUp(fr::frame_100 &frm_100){
    int8_t brk = frm_100.get_brake() + 10;
    if (brk > 100)
        brk = 100;
    frm_100.set_brake(brk);
}
void Conversion::BrakePedalDown(fr::frame_100 &frm_100){
    int8_t brk = frm_100.get_brake() - 10;
    if (brk < 0)
        brk = 0;
    frm_100.set_brake(brk);
}
void Conversion::SetStartButton(fr::frame_100 &frm_100){
    frm_100.set_startstop(fr::StartButtonSts::PRESSED);
}
void Conversion::ReleaseStartButton(fr::frame_100 &frm_100){
    frm_100.set_startstop(fr::StartButtonSts::UNPRESSED);
}
void Conversion::GearLeverUp(fr::frame_100 &frm_100){

    switch(frm_100.get_gearlever())
    {
        case fr::GearLeverPos::PARK:
            frm_100.set_gearlever(fr::GearLeverPos::REVERSE);
            break;
        case fr::GearLeverPos::REVERSE:
            frm_100.set_gearlever(fr::GearLeverPos::NEUTRAL);
            break;      
        case fr::GearLeverPos::NEUTRAL:
            frm_100.set_gearlever(fr::GearLeverPos::DRIVE);
            break;    
        case fr::GearLeverPos::DRIVE:
            frm_100.set_gearlever(fr::GearLeverPos::DRIVE);
            break;                       
        default:
            frm_100.set_gearlever(fr::GearLeverPos::PARK);
    }
}

void Conversion::GearLeverDown(fr::frame_100 &frm_100){

    switch(frm_100.get_gearlever())
    {
        case fr::GearLeverPos::PARK:
            frm_100.set_gearlever(fr::GearLeverPos::PARK);
            break;
        case fr::GearLeverPos::REVERSE:
            frm_100.set_gearlever(fr::GearLeverPos::PARK);
            break;      
        case fr::GearLeverPos::NEUTRAL:
            frm_100.set_gearlever(fr::GearLeverPos::REVERSE);
            break;    
        case fr::GearLeverPos::DRIVE:
            frm_100.set_gearlever(fr::GearLeverPos::NEUTRAL);
            break;                       
        default:
            frm_100.set_gearlever(fr::GearLeverPos::PARK);
    }
}

void Conversion::SetSimulationMode(fr::frame_100 &frm_100){

    switch(frm_100.get_mode())
    {
        case fr::SimulationMode::SLEEP:
            frm_100.set_mode(fr::SimulationMode::INACTIVE);
            break;
        case fr::SimulationMode::INACTIVE:
            frm_100.set_mode(fr::SimulationMode::ACTIVE);
            break;
        case fr::SimulationMode::ACTIVE:
            frm_100.set_mode(fr::SimulationMode::OFF);
            break;     
        default:
            frm_100.set_mode(fr::SimulationMode::SLEEP);          
    }
}

void  Conversion::fillFrame(fr::frame_100 &frm_100, kc::UserReq _userReq){
   
    switch (_userReq){
        case kc::UserReq::SIMULATION_MODE: // m
            SetSimulationMode(frm_100);
            break;      
        case  kc::UserReq::ACC_PED_UP: // Arrow UP
            AccPedUp(frm_100);
            break;
        case  kc::UserReq::ACC_PED_DOWN: //Arrow Down
            AccPedDown(frm_100);
            break;
        case kc::UserReq::STARTBUTTON: // s
            SetStartButton(frm_100);
            break;
        case kc::UserReq::BRAKE_PED_UP: //->
            BrakePedalUp(frm_100);
            break;
        case kc::UserReq::BRAKE_PED_DOWN: //<-
            BrakePedalDown(frm_100);
            break;
        case kc::UserReq::GEARLEV_UP: //+
            GearLeverUp(frm_100);
            break;
        case kc::UserReq::GEARLEV_DOWN: //-
            GearLeverDown(frm_100);
            break;
        default:  
            ReleaseStartButton(frm_100);   // NOT OK SOLUTION NEED IMPROVMENT      
    }
    //std::cout << "&data_to_send = " << &data_to_send << " &data_to_send+6 " << &data_to_send+6 << std::endl;
    frm_100.set_updatebit(1);
}

Conversion::~Conversion(){
    //empty
}