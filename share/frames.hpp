#ifndef _FRAMES_H
#define _FRAMES_H
#include <cstdint>

struct fr100{
//header
    uint32_t canid = 100;; 
    uint8_t candlc = 8;
    uint8_t canpad = 0;
    uint8_t canres0 = 0;
    uint8_t canres1 = 0;
//data
    unsigned accelerator:8;
    unsigned brake:8;
    unsigned startstop:1;
    unsigned mode:2;
    unsigned gearlever:4;
    unsigned updatebit:1;
    unsigned res0:8;
    unsigned res1:8;
    unsigned res2:8;
    unsigned res3:8;  
    unsigned res4:8;     
};

struct fr200{
//header
    uint32_t canid = 200;; 
    uint8_t candlc = 8;
    uint8_t canpad = 0;
    uint8_t canres0 = 0;
    uint8_t canres1 = 0;
//data
    unsigned rpm:16;
    unsigned fuel:16;
    unsigned driverinfo:4;
    unsigned telltale:3;
    unsigned updatebit:1;
    unsigned res0:8;
    unsigned res1:8;
    unsigned res2:8;     
};

struct fr300{
//header
    uint32_t canid = 300;
    uint8_t candlc = 8;
    uint8_t canpad = 0;
    uint8_t canres0 = 0;
    uint8_t canres1 = 0;
//data
    unsigned speed:16;
    unsigned gearactual:7;
    unsigned updatebit:1;
    unsigned res0:8;
    unsigned res1:8;
    unsigned res2:8;
    unsigned res3:8;  
    unsigned res4:8;     
};

#endif