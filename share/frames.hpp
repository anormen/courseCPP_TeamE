#ifndef _FRAMES_H
#define _FRAMES_H
#include <cstdint>

enum class GearLeverPos {PARK = 0, REVERSE = 1, NEUTRAL = 2, DRIVE = 3};
enum class StartButtonSts {UNPRESSED = 0, PRESSED = 1};
enum class SimulationMode { OFF = 0, INACTIVE = 1, ACTIVE = 2 , SLEEP = 3};
enum class DriverInformation { NO_MSG = 0, NO_BRAKE = 1, NOT_IN_P = 2, NOT_IN_P_IN_D = 3 };

//Farme cycle times
const uint16_t fr100_updateRate = 200;
const uint16_t fr200_updateRate = 200;
const uint16_t fr300_updateRate = 200;

//frme from inputhandler
struct fr100{
//header
    uint32_t canid = 100;; 
    uint8_t candlc = 8;
    uint8_t canpad = 0;
    uint8_t canres0 = 0;
    uint8_t canres1 = 0;
//data
    uint8_t accelerator:8;
    uint8_t brake:8;
    StartButtonSts startstop:1;
    SimulationMode mode:2;
    GearLeverPos gearlever:4;
    bool updatebit:1;
    uint8_t res0:8;
    uint8_t res1:8;
    uint8_t res2:8;
    uint8_t res3:8;  
    uint8_t res4:8;     
};
//frame from ECM
struct fr200{
//header
    uint32_t canid = 200;; 
    uint8_t candlc = 8;
    uint8_t canpad = 0;
    uint8_t canres0 = 0;
    uint8_t canres1 = 0;
//data
    uint16_t rpm:16;
    uint16_t fuel:16;
    DriverInformation driverinfo:4;
    unsigned telltale:3;
    bool updatebit:1;
    uint8_t res0:8;
    uint8_t res1:8;
    uint8_t res2:8;     
};
//frame from TCM
struct fr300{
//header
    uint32_t canid = 300;
    uint8_t candlc = 8;
    uint8_t canpad = 0;
    uint8_t canres0 = 0;
    uint8_t canres1 = 0;
//data
    uint16_t speed:16;
    unsigned gearactual:7;
    bool updatebit:1;
    uint8_t res0:8;
    uint8_t res1:8;
    uint8_t res2:8;
    uint8_t res3:8;  
    uint8_t res4:8;     
};

#endif