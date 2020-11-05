#include "TCM.hpp"

int TCM::GetGear(){return this->gear;}

unsigned int TCM::CalculateGear(unsigned int RPM){
    if(RPM>1200){
        gear+=1;
        RPM+=-300;
    }
    return RPM;
}