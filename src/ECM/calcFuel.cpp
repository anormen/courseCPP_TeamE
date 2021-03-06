#include "calcFuel.hpp"

calcFuel::calcFuel(){

    for (int i = 0; i < fuelInstFilterSamples; i++)
        fuelInstFilter.push_front(0.00165);    // defaut init 6*0.9l/h

    for (int i = 0; i < fuelAvgFilterSamples; i++)
        fuelAvgFilter.push_front(fA);    // defaut init 50km/h 5L/km100   
}

void calcFuel::CalculateFuel(const uint8_t &accelerator, const uint16_t &rpm, const uint16_t &speed){
  
    //deside fuel rate
    if(rpm > 0) { //running

        fuelticks += CalculateRate(accelerator, rpm, speed);

        uint32_t filterDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-startTime).count();
        if(filterDuration > fuelInstFilterTime){

            startTime = std::chrono::steady_clock::now();
            if(speed > 0){//AVG

                fuelAvgFilter.pop_back();
                fA.vSpeed = speed;
                fA.iFuel = (fuelticks-fuelticksPrev) * (1000.0/fuelInstFilterTime);
                fuelAvgFilter.push_front(fA);
                double sumOfvSpeed=0, sumOfFuel=0;
                //calc average speed and injected fuel
                for(auto i : fuelAvgFilter) {
                    sumOfvSpeed += i.vSpeed;
                    sumOfFuel += i.iFuel;
                }
                fuelAvg = ((sumOfFuel/fuelAvgFilterSamples) * 3600) / (sumOfvSpeed/fuelAvgFilterSamples) * 100;
            }
            else{ //INST
                fuelInstFilter.pop_back();
                fuelInstFilter.push_front((fuelticks-fuelticksPrev) * (1000.0/fuelInstFilterTime)); //fuelticks per sample
                //calc average  -> l/h for stand still
                double sumOfiFuel = std::accumulate(fuelInstFilter.begin(), fuelInstFilter.end(), 0.0);
                fuelInst = (sumOfiFuel/fuelInstFilterSamples) * 3600; // AccumulatedSumOfSamples/NumberOfSamples * s/h 
            }
            fuelticksPrev = fuelticks;
        }
    }
    //debug
 //std::cout << " ticks: " << fuelticks << " rate: " << CalculateRate(accelerator, rpm, speed) << " avg: " << fuelAvg << " inst: " << fuelInst << " speed: " << speed << std::endl;   
} 

double calcFuel::CalculateRate(const uint8_t &accelerator, const uint16_t &rpm, const uint16_t &speed){

    double rate;
    //deside fuel rate
    if(accelerator > 0){ //accelerating

        if(speed > 0){ //moving with load
            rate = baseRate * rpm * (accelerator/9.0); //divide by some constant....
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
    rate = rate / updateRate; // main run 4 times per second 250ms

    return rate;
}