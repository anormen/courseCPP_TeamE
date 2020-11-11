#ifndef _FRAMES_H
#define _FRAMES_H
#include <cstdint>
#include <vector>
#include <string>

enum class GearLeverPos : uint8_t {PARK, REVERSE, NEUTRAL, DRIVE};
enum class StartButtonSts : uint8_t {UNPRESSED, PRESSED};
enum class SimulationMode : uint8_t { SLEEP, INACTIVE, ACTIVE, OFF};
enum class DriverInformation : uint8_t { NO_MSG, NO_BRAKE, NOT_IN_P, NOT_IN_P_IN_D};
static std::vector<std::string> messages = {"No message", "No Brake pressed", "Gear not in P" , "Gear in D, select P or hold for 5sec"};
static std::vector<std::string> gears = {"P", "R", "N" , "D" , "1", "2", "3", "4", "5", "6" };
static std::vector<std::string> modes = { "SLEEP", "INACTIVE", "ACTIVE", "OFF" };

//frame cycle times
const uint16_t fr100_updateRate = 200;
const uint16_t fr200_updateRate = 200;
const uint16_t fr300_updateRate = 200;

//frame from inputhandler
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
    uint8_t startstop:1;
    uint8_t mode:2;
    uint8_t gearlever:4;
    uint8_t updatebit:1;
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
    uint8_t driverinfo:4;
    uint8_t telltale:3;
    uint8_t updatebit:1;
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
    uint8_t gearactual:7;
    uint8_t updatebit:1;
    uint8_t res0:8;
    uint8_t res1:8;
    uint8_t res2:8;
    uint8_t res3:8;  
    uint8_t res4:8;     
};

#endif