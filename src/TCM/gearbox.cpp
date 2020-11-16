#include "gearbox.hpp"

 Gearbox::Gearbox(){

        currentGear = 1;
        targetGear = 1;
        
    }

// VehicleSpeed (km/h) = egRPM ( round per minut)* gearRatio (total with scaling 1000) * 
//wheelRadiusCircumferance in m 60 for rpm
int Gearbox::getVehicleSpeed(int _engRpm)
{
    int vehicleSpeed = (_engRpm * getGearRatio(_engRpm) * wheelCircumference)*6/(10000);
    return ( vehicleSpeed);
}
// GearRation 
int Gearbox::getGearRatio (int _engRpm)
{  
    return ( gearRatioFact[targetGear]);
}

void Gearbox::selectGear(const int accPedal, const int _engRpm) {
    int accPedIndex = int (accPedal/10);

    if (currentGear == 1){
        if ((gearMapUpShift12[accPedIndex] < _engRpm))
            targetGear = 2;}
    else if(currentGear == 2)
    {
        if ((gearMapUpShift12[accPedIndex] + gearChangeHyst) > _engRpm)
            targetGear = 1;
        else if (gearMapUpShift23[accPedIndex] < _engRpm)
            targetGear = 3;
    }
    else if (currentGear == 3 ){
        if ((gearMapUpShift12[accPedIndex] + gearChangeHyst) > _engRpm)
            targetGear = 2;
        else if (gearMapUpShift23[accPedIndex] < _engRpm)
            targetGear = 4;
    } 
        else if(currentGear == 4 ){
        if ((gearMapUpShift12[accPedIndex] + gearChangeHyst) > _engRpm)
            targetGear = 3;
        else if (gearMapUpShift23[accPedIndex] < _engRpm)
            targetGear = 5;

    }else  /* currentGear == 5*/
        if ((gearMapUpShift12[accPedIndex] + gearChangeHyst) > _engRpm)
            targetGear = 4;
    
    std::cout << currentGear << " " << targetGear  << "print in selectGear\n\r";
    currentGear = targetGear;
}


Gearbox::~Gearbox(){};