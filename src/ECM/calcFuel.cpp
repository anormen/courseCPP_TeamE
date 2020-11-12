#include "calcFuel.hpp"

calcFuel::calcFuel(){

    startTime = std::chrono::steady_clock::now();
    for (int i = 0; i < fuelInstFilterSamples; i++)
        fuelInstFilter.push_front(0.00165);    // defaut init 6*0.9l/h

    for (int i = 0; i < fuelAvgFilterSamples; i++)
        fuelAvgFilter.push_front(fA);    // defaut init 50km/h 5L/km100   
}

void calcFuel::update(){

    uint16_t rpm = updateRpm();
    uint16_t speed = updateVehicleSpeed();
    uint8_t accelerator = updateAccelerator();
    double sumOfiFuel=0, sumOfSpeed=0, sumOfFuel=0;
    //deside fuel rate
    if(rpm > 0) { //running

        if(accelerator > 0){ //accelerating

            if(speed > 0){ //moving with load
                rate = baseRate * rpm * (accelerator/9.0);
            }
            else { //stand still reving no load
                rate = baseRate * rpm; //2.3l/h @ 2000rpm @ 250ms update
            }
        }
        else { //idle or coasting
            if(speed > 0){ //coasting
                rate = 0 ;
            }
            else{ //idle
                rate = baseRate * rpm; //0.9l/h @ 750 rpm @ 250ms update
            }
        }
        fuelticks += rate / 4.0; // main run 4 times per second 250ms
    }

    timeoutT = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-startTime).count();
    if(timeoutT >= fuelInstFilterTime){

        startTime = std::chrono::steady_clock::now();
        fuelInstFilter.pop_back();
        fuelInstFilter.push_front((fuelticks-fuelticksPrev) * (1000.0/fuelInstFilterTime)); //fuelticks per sample

        for(auto i : fuelInstFilter) //sum elements
                sumOfiFuel += i;
        //calc average  -> l/h for stand still
        fuelInst = (sumOfiFuel/fuelInstFilterSamples) * 3600; // AccumulatedSumOfSamples/NumberOfSamples * s/h 
  
        if(speed > 0){

            fuelAvgFilter.pop_back();
            fA.vSpeed = speed;
            fA.iFuel = (fuelticks-fuelticksPrev) * (1000.0/fuelInstFilterTime);
            fuelAvgFilter.push_front(fA);
            //calc average speed and injected fuel
            for(auto i : fuelAvgFilter) {
                sumOfSpeed += i.vSpeed;
                sumOfFuel += i.iFuel;
            }
            fuelAvg = ((sumOfFuel/fuelInstFilterSamples) * 3600) / (sumOfSpeed/fuelInstFilterSamples) * 100;//(1000.0/3600.0) * 3600.0 / 10.0;
        }
        fuelticksPrev = fuelticks;
    }
    //debug
    std::cout << " ticks: " << fuelticks << " rate: " << rate << " avg: " << fuelAvg << " inst: " << fuelInst << std::endl;    
};

uint16_t calcFuel::updateRpm(){
    //get value from internal ECM
    return 4500;
};
        
uint8_t calcFuel::updateAccelerator(){
    //get value from fr100 uint8_t accelerator:8;
    return 100;
};
        
uint16_t calcFuel::updateVehicleSpeed(){
    //get value from fr300 uint16_t speed:16;
    return 120;
};

void calcFuel::updateFuelAvg(){
    //send on can fr200 uint16_t fuel:16;
    std::cout << "INST: " << fuelInst << std::endl; //debug
};

void calcFuel::updateFuelInst(){
    //not sent yet
    std::cout << "AVG: " << fuelAvg << std::endl; //debug
};