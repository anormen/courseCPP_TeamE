#include "TCM.hpp"

int TCM::GetGear(){return this->gear;}

void TCM::CalculateGear(int &RPM){
    if(RPM>1200){
        gear+=1;
        RPM+=-300;
    }
        
}