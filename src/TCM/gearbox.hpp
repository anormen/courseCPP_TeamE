#ifndef GEARBOX_H
#define GEARBOX_H
#include<iostream>
#include<cmath>

class Gearbox {
private:
    const int gearRatioFact[6] = {11, 10, 16, 22, 30, 40}; // R=0, 1,2 3,4,5
    const int wheelCircumference = 2;// 2m 1913 mmmm for 17 tums
    
    // Select gear based on egRpm and AccPedal
    // Accped                            0,     10,   20,   30,   40,   50,   60,   70,   80,   90,  100
    const int gearMapUpShift12[11] =   {1800, 2100, 2500, 3500, 3000, 3500, 3500, 3500, 3500, 4500, 5000 }; //rpm
    const int gearMapUpShift23[11] =   {1800, 2100, 3000, 3500, 4000, 4500, 4500, 4500, 4500, 4500, 5000 }; //rpm
    const int gearMapUpShift34[11] =   {1800, 2100, 3000, 3500, 4000, 4500, 4500, 4500, 4500, 4500, 5500 }; //rpm
    const int gearMapUpShift45[11] =   {1800, 2100, 3000, 3500, 4000, 4500, 4500, 4500, 4500, 4500, 5500 }; //rpm    
    int gearChangeHyst = 100; // rpm

    int currentGear;
    int targetGear;

public:
    Gearbox();
    ~Gearbox();

    // VehicleSpeed (m/s) = egRPM ( round per minut)* gearRatio (total with scaling 10) * 
    //wheelRadius  dived with 1000 for wheelradius in mm and with 10 for gearRatio scaling 10 and 60 for rpm
    int getVehicleSpeed(int _engRpm);

    // GearRation 
    int getGearRatio (int _engRpm);

    void selectGear(const int accPedal, const int _engRpm);

};


#endif // GEARBOX_H