#include "ECM.hpp"


ECM::ECM(){
    //this->RPM=900;
    this->eng_on=false;

}

void ECM::CalculateRPM(int acc_ped){
    if(this->eng_on==true){
        if(this->RPM<900)
            this->RPM=900;
        this->RPM+=50*acc_ped/50;
        if(this->RPM > 8000)
            this->RPM=7600;
    } else {
        this->RPM=0;
    }
    
    //tcm.CalculateGear(this->RPM);
}

void ECM::UpdateECM(int acc_ped, uint8_t startstop){
    if(startstop==1)
        this->eng_on=!eng_on;

    this->CalculateRPM(acc_ped);
}

int ECM::GetRPM(){return RPM;}