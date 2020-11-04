#ifndef FRAMEPACKAGING_H
#define FRAMEPACKAGING_H
#include <stdint.h>
/* File defining the frame content sent by InputHandler*/

enum class GearLeverPos {PARK, REVERSE, NEUTRAL, DRIVE};
enum class StartButtonSts {UNPRESSED, PRESSED};
enum class SimulationMode {INACTIVE, ACTIVE };

union {
    Frame_data frameDataSet;
    uint8_t frameDataArray[8];
} frameData;


// Start with 8 byte frame to keep it simplaer
struct Frame_data {
        uint8_t accPedal;           //0-100%
        uint8_t brakePedal;         //0-100%
        StartButtonSts startButton;       // ON = 1 OFF =0
        GearLeverPos gearLever; // PRND P=0, R=1, N=2, D=3
        uint8_t simulationMode;     // Active = 0, Inactive = 1;
     };
int Frame_id = 100;

#endif