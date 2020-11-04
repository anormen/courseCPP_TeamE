#include "ECM.hpp"

// constructor
// destructor
// calc RPM

ECM::ECM(){this->RPM=900;}

void ECM::CalculateRPM(int acc_ped){
    this->RPM+=50*acc_ped/100;
    if(this->RPM > 8000)
        this->RPM=7600;
}

int ECM::GetRPM(){return RPM;}