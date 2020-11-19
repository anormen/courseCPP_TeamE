#include "gearbox.hpp"

Gearbox::Gearbox()
{

    currentGear = 1;
    targetGear = 1;
}

 void Gearbox::setGearleverPos(frames::GearLeverPos _gearleverPos)
 {
     this->gearleverPosition = _gearleverPos;
 }
int Gearbox::getVehicleSpeed()
{
    return (double (lastVehicleSpeed100/100));
}

void Gearbox::calculateVehicleSpeed(const int _accPed, const int _engRpm, const frames::GearLeverPos _gearleverPosition)
{
    int vehicleSpeed = 1;

    std::cout << vehicleSpeed << " getVehicleSpeeda  " << lastVehicleSpeed100 << " " << _engRpm << std::endl;

    switch(this->gearleverPosition)
    {
        // PARK: Speed = 0 
        case frames::GearLeverPos::PARK:
        {
            vehicleSpeed = 0;
            std::cout << "PARK" << vehicleSpeed << std::endl;
            break;
        }
            
        // REVERSE: //Not implemented    
        case frames::GearLeverPos::REVERSE:
            // not implemnt;
            break;     
        // NEUTRAL: vehicleSpeed = lastvehicleSpeed100/100; slow retard to 0 
        case frames::GearLeverPos::NEUTRAL:
            if (this->lastVehicleSpeed100 > 0){
                this->lastVehicleSpeed100--;
                vehicleSpeed = double(this->lastVehicleSpeed100/100);
            }
                    
            break;   
        // DRIVE:      
        case frames::GearLeverPos::DRIVE:
        {
            //handling idle

            
            if ((_engRpm <= 900) && (_accPed == 0))
            {
                if (this->lastVehicleSpeed100 > 0)
                {
                    this->lastVehicleSpeed100--;
                    vehicleSpeed = (double)(this->lastVehicleSpeed100/100);
                }   
            }
            else
            {
                // VehicleSpeed (km/h) = egRPM ( round per minut)* gearRatio (total with scaling 1000) *
                //wheelRadiusCircumferance in m 60 for rpm  
                int tempVehicleSpeed = 0;    
                tempVehicleSpeed = (double)(_engRpm * getGearRatio() * wheelCircumference) * 6 / (10000);
                std::cout << tempVehicleSpeed << std::endl;
                
                int speedDelta = tempVehicleSpeed -(double)(lastVehicleSpeed100/100);
                // Filter max rate change
                const int maxSpeedDelta = 2; //km/h per tick
                
                if (speedDelta > maxSpeedDelta)
                {
                    vehicleSpeed = (double)lastVehicleSpeed100/100 + maxSpeedDelta;
                }
                    
                else if (speedDelta < (-maxSpeedDelta))
                {
                    vehicleSpeed = (double)lastVehicleSpeed100/100 - maxSpeedDelta;
                }
                else
                {
                    vehicleSpeed = tempVehicleSpeed;
                }
            }
            
            std::cout << "DRIVE a " << vehicleSpeed << std::endl;
        }
        break;                       
        default:
            std::cout << "Undefined gearlever";
    }

    lastVehicleSpeed100 = vehicleSpeed*100;
}
// GearRation
int Gearbox::getGearRatio() 
{
    return (gearRatioFact[targetGear]);
}

int Gearbox::getGear()
{
    return (currentGear);
}

void Gearbox::selectGear(const int accPedal, const int _engRpm) {
    int accPedIndex = int (accPedal/10);
    if ( gearleverPosition == frames::GearLeverPos::PARK)
        return;

    if (multiShiftDelay < 20){
        multiShiftDelay++;
    }       
    else {   
        if (currentGear == 1){
            if ((_engRpm > gearMapUpShift12[accPedIndex]))
                targetGear = 2;}
        else if(currentGear == 2)
        {
            if (_engRpm < ((double)gearMapUpShift12[accPedIndex]* ((double)gearRatioFact[1]/(double)gearRatioFact[2])))
                targetGear = 1;
            else if (_engRpm > gearMapUpShift23[accPedIndex])
                targetGear = 3;
        }
        else if (currentGear == 3 ){
            if (_engRpm < ((double)gearMapUpShift23[accPedIndex]* ((double)gearRatioFact[2]/(double)gearRatioFact[3])))
                targetGear = 2;
            else if (_engRpm > gearMapUpShift34[accPedIndex])
                targetGear = 4;
        } 
            else if(currentGear == 4 ){
            if (_engRpm < ((double)gearMapUpShift34[accPedIndex]* ((double)gearRatioFact[3]/(double)gearRatioFact[4])))
                targetGear = 3;
            else if (_engRpm > gearMapUpShift45[accPedIndex])
                targetGear = 5;
        }
        else  /* currentGear == 5*/
            if (_engRpm < ((double)gearMapUpShift45[accPedIndex]* ((double)gearRatioFact[4]/(double)gearRatioFact[5])))
                targetGear = 4;

    if (targetGear != currentGear)
        multiShiftDelay = 0;      
    
    }
    std::cout << multiShiftDelay <<  "multi" << targetGear << std::endl;       
    
    std::cout << currentGear << " " << targetGear  << "print in selectGear\n\r";
    currentGear = targetGear;
}

Gearbox::~Gearbox(){};