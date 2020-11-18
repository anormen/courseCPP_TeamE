#include "gearbox.hpp"

Gearbox::Gearbox()
{

    currentGear = 1;
    targetGear = 1;
}

// VehicleSpeed (km/h) = egRPM ( round per minut)* gearRatio (total with scaling 1000) *
//wheelRadiusCircumferance in m 60 for rpm
int Gearbox::getVehicleSpeed(const int _accPed, const int _engRpm)
{
    int vehicleSpeed;

    std::cout << vehicleSpeed << "  " << lastVehicleSpeed << " " << _engRpm << std::endl;

    if ((_engRpm <= 900) && (_accPed == 0))
    {
        if (this->lastVehicleSpeed > 0)
            this->lastVehicleSpeed--;

        vehicleSpeed = this->lastVehicleSpeed;
    }
    //else if (geae)  PARK and NEUTTRALm
    else
    {
        vehicleSpeed = (_engRpm * getGearRatio(_engRpm) * wheelCircumference) * 6 / (10000);
        lastVehicleSpeed = vehicleSpeed;
    }
    return (vehicleSpeed);
}
// GearRation
int Gearbox::getGearRatio(int _engRpm)
{
    return (gearRatioFact[targetGear]);
}

int Gearbox::getGear()
{
    return (currentGear);
}

void Gearbox::selectGear(const int accPedal, const int _engRpm) {
    int accPedIndex = int (accPedal/10);
    
    if (multiShiftDelay < 20){
        multiShiftDelay++;
    }       
    else {   
        if (currentGear == 1){
            if ((_engRpm > gearMapUpShift12[accPedIndex]))
                targetGear = 2;}
        else if(currentGear == 2)
        {
            if (_engRpm < (gearMapUpShift12[accPedIndex]* (gearRatioFact[1]/gearRatioFact[2])))
                targetGear = 1;
            else if (_engRpm > gearMapUpShift23[accPedIndex])
                targetGear = 3;
        }
        else if (currentGear == 3 ){
            if (_engRpm < (gearMapUpShift23[accPedIndex]* (gearRatioFact[2]/gearRatioFact[3])))
                targetGear = 2;
            else if (_engRpm > gearMapUpShift34[accPedIndex])
                targetGear = 4;
        } 
            else if(currentGear == 4 ){
            if (_engRpm < (gearMapUpShift34[accPedIndex]* (gearRatioFact[3]/gearRatioFact[4])))
                targetGear = 3;
            else if (_engRpm > gearMapUpShift45[accPedIndex])
                targetGear = 5;
        }
        else  /* currentGear == 5*/
            if (_engRpm < (gearMapUpShift45[accPedIndex]* (gearRatioFact[4]/gearRatioFact[5])))
                targetGear = 4;

    if (targetGear != currentGear)
        multiShiftDelay = 0;      
    
    }
    std::cout << multiShiftDelay <<  "multi" << targetGear << std::endl;       
    
    std::cout << currentGear << " " << targetGear  << "print in selectGear\n\r";
    currentGear = targetGear;
}

Gearbox::~Gearbox(){};