#include "calcFuel.hpp"

calcFuel::calcFuel(){

    startTime = std::chrono::steady_clock::now();
    for (int i = 0; i < fuelInstFilterSamples; i++)
        fuelInstFilter.push_front(0.00165);    // defaut init 6*0.9l/h

    for (int i = 0; i < fuelAvgFilterSamples; i++)
        fuelAvgFilter.push_front(fA);    // defaut init 50km/h 5L/km100   
}

void calcFuel::CalculateFuel(frame_100 &fr100, uint16_t &rpm, frame_300 &fr300){

    //uint16_t rpm = fr200.get_rpm();
    uint16_t speed = fr300.get_speed();
    uint8_t accelerator = fr100.get_accelerator();
    double sumOfiFuel=0, sumOfSpeed=0, sumOfFuel=0;
    double rate = 0;

    //deside fuel rate
    if(rpm > 0) { //running

        rate = CalculateRate(accelerator, rpm, speed);
        fuelticks += rate;

        uint32_t filterDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-startTime).count();
        if(filterDuration > fuelInstFilterTime){

            startTime = std::chrono::steady_clock::now();
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
                fuelAvg = ((sumOfFuel/fuelAvgFilterSamples) * 3600) / (sumOfSpeed/fuelAvgFilterSamples) * 100;
            }
            else{
                fuelInstFilter.pop_back();
                fuelInstFilter.push_front((fuelticks-fuelticksPrev) * (1000.0/fuelInstFilterTime)); //fuelticks per sample

                for(auto i : fuelInstFilter) //sum elements
                    sumOfiFuel += i;
                //calc average  -> l/h for stand still
                fuelInst = (sumOfiFuel/fuelInstFilterSamples) * 3600; // AccumulatedSumOfSamples/NumberOfSamples * s/h 
            }
            fuelticksPrev = fuelticks;
        }
    }
    //debug
    std::cout << " ticks: " << fuelticks << " rate: " << rate << " avg: " << fuelAvg << " inst: " << fuelInst << std::endl;   
} 

double calcFuel::CalculateRate(uint8_t &accelerator, uint16_t &rpm, uint16_t &speed){

    double rate = 0;
    //deside fuel rate

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
    rate = rate / 4.0; // main run 4 times per second 250ms

    return rate;
}