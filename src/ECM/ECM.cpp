#include "ECM.hpp"


// constructor
// destructor
// calc RPM

ECM::ECM(){
    this->RPM=900;

}

void ECM::CalculateRPM(int acc_ped, bool eng_on){
    if(eng_on==true){
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

int ECM::GetRPM(){return RPM;}