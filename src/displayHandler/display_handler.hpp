#ifndef _DISPLAY_HANDLER_H_
#define _DISPLAY_HANDLER_H_

#include "display_class.h"
#include "frames.hpp"
#include "can_class.h"

class displayHandler{
    public:
        displayHandler();
        void run();
        ~displayHandler(){};
    private:
        can_frame frameGen;
        fr100 frame100;
        fr200 frame200;
        fr300 frame300;
        display dispHndl;
        canHandler canHndl;
        uint16_t displayUpdateRate = 500;
};

#endif