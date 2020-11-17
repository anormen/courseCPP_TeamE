#include "conversion.hpp"

Conversion::Conversion(){
    // Empty
}
void Conversion::AccPedUp(){
    uint8_t acc = this->fr100_to_send.get_accelerator() + 10;
    if(acc > 100)
        acc = 100;
    fr100_to_send.set_accelerator(acc);
}
void Conversion::AccPedDown(){     
    uint8_t acc = this->fr100_to_send.get_accelerator() - 10; 
    if (acc >10) { 
        acc = acc - 10;
    }
    else {
        acc = 0;
    }
    fr100_to_send.set_accelerator(acc);
}
void Conversion::BrakePedalUp(){
    uint8_t brk = this->fr100_to_send.get_brake() + 10;
    if (brk > 100) { 
        brk = 100;
    }
    fr100_to_send.set_brake(brk);
}
void Conversion::BrakePedalDown(){
    uint8_t brk = this->fr100_to_send.get_brake() - 10;
    if (brk >10) { 
        brk = brk - 10;
    }
    else {
        brk = 0;
    }
    this->fr100_to_send.set_brake(brk);
}
void Conversion::SetStartButton(){
        this->fr100_to_send.set_startstop(StartButtonSts::PRESSED);
}
void Conversion::ReleaseStartButton(){
         this->fr100_to_send.set_startstop(StartButtonSts::UNPRESSED);
}
void Conversion::GearLeverUp(){

        switch(this->fr100_to_send.get_gearlever())
        {
            case GearLeverPos::PARK:
                this->fr100_to_send.set_gearlever(GearLeverPos::REVERSE);
                break;
            case GearLeverPos::REVERSE:
                this->fr100_to_send.set_gearlever(GearLeverPos::NEUTRAL);
                break;      
            case GearLeverPos::NEUTRAL:
                this->fr100_to_send.set_gearlever(GearLeverPos::DRIVE);
                break;    
            case GearLeverPos::DRIVE:
                this->fr100_to_send.set_gearlever(GearLeverPos::DRIVE);
                break;                       
            default:
                this->fr100_to_send.set_gearlever(GearLeverPos::PARK);
        }
}

void Conversion::GearLeverDown(){

        switch(this->fr100_to_send.get_gearlever())
        {
            case GearLeverPos::PARK:
                this->fr100_to_send.set_gearlever(GearLeverPos::PARK);
                break;
            case GearLeverPos::REVERSE:
                this->fr100_to_send.set_gearlever(GearLeverPos::PARK);
                break;      
            case GearLeverPos::NEUTRAL:
                this->fr100_to_send.set_gearlever(GearLeverPos::REVERSE);
                break;    
            case GearLeverPos::DRIVE:
                this->fr100_to_send.set_gearlever(GearLeverPos::NEUTRAL);
                break;                       
            default:
                this->fr100_to_send.set_gearlever(GearLeverPos::PARK);
        }
}

void Conversion::SetSimulationMode(){

    switch(this->fr100_to_send.get_mode())
    {
        case SimulationMode::SLEEP:
            this->fr100_to_send.set_mode(SimulationMode::INACTIVE);
            break;
        case SimulationMode::INACTIVE:
            this->fr100_to_send.set_mode(SimulationMode::ACTIVE);
            break;
        case SimulationMode::ACTIVE:
            this->fr100_to_send.set_mode(SimulationMode::OFF);
            break;     
        default:
            this->fr100_to_send.set_mode(SimulationMode::SLEEP);          
    }
    //mode = fr100_to_send.get_mode();
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
        case kc::UserReq::BRAKE_PED_UP: //
            BrakePedalUp();
            break;
        case kc::UserReq::BRAKE_PED_DOWN: //
            BrakePedalDown();
            break;
        case kc::UserReq::GEARLEV_UP:
            GearLeverUp();
            break;
        case kc::UserReq::GEARLEV_DOWN:
            GearLeverDown();
            break;
        default:  
            ReleaseStartButton();   // NOT OK SOLUTION NEED IMPROVMENT      
    }
    //std::cout << "&data_to_send = " << &data_to_send << " &data_to_send+6 " << &data_to_send+6 << std::endl;
    memcpy(&_frame,fr100_to_send.get_frame_ptr(),sizeof(_frame));
}

Conversion::~Conversion(){}