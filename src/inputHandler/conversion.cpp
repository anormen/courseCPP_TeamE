#include "conversion.hpp"

bool exeRequest(fr::frame_100& frame, kc::UserReq action)
{
    bool isExe = false;
    auto func = enumActionToFunc.find(action);
    if (func == enumActionToFunc.end()) 
        std::cout << "Action: " << (int)action << " not found\n\r"; 
    else {
        std::cout << "Action: " << (int)action << " Function addr: " << &func->second << "\n\r"; 
        func->second(frame);
        isExe = true;
    }
    return isExe;
}

void AccPedUp(fr::frame_100 &frm_100){
    int8_t acc = frm_100.get_accelerator() + 10;
    acc > 100 ? frm_100.set_accelerator(100) : frm_100.set_accelerator(acc);
    frm_100.set_updatebit(1);    
}
void AccPedDown(fr::frame_100 &frm_100){     
    int8_t acc = frm_100.get_accelerator() - 10; 
    acc < 0 ? frm_100.set_accelerator(0) : frm_100.set_accelerator(acc);
    frm_100.set_updatebit(1);    
}
void BrakePedalUp(fr::frame_100 &frm_100){
    int8_t brk = frm_100.get_brake() + 10;
    brk > 100 ? frm_100.set_brake(100) : frm_100.set_brake(brk);
    frm_100.set_updatebit(1);    
}
void BrakePedalDown(fr::frame_100 &frm_100){
    int8_t brk = frm_100.get_brake() - 10;
    brk < 0 ? frm_100.set_brake(0) : frm_100.set_brake(brk);
    frm_100.set_updatebit(1);
}
void SetStartButton(fr::frame_100 &frm_100){
    
    frm_100.set_startstop(fr::StartButtonSts::PRESSED);
    frm_100.set_updatebit(1);
}
void ReleaseStartButton(fr::frame_100 &frm_100){
    
    frm_100.set_startstop(fr::StartButtonSts::UNPRESSED);
    frm_100.set_updatebit(1);
}
void GearLeverUp(fr::frame_100 &frm_100){

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
    frm_100.set_updatebit(1);    
}

void GearLeverDown(fr::frame_100 &frm_100){

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
    frm_100.set_updatebit(1);    
}

void SetSimulationMode(fr::frame_100 &frm_100){

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
    frm_100.set_updatebit(1);
}