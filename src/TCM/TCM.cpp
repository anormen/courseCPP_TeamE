#include "TCM.hpp"

int TCM::GetGear(){return this->gear;}

void TCM::CalculateGear(int &RPM){
    if(RPM>3000){
        this->gear+=1;
        RPM=900;
    }
    
}