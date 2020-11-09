#ifndef _DISPLAY_HANDLER_H_
#define _DISPLAY_HANDLER_H_

#include "display_class.hpp"
#include "frames.hpp"
#include "can_class.h"
#include "data_class.hpp"

class displayHandler{
    public:
        displayHandler();
        void run();
        ~displayHandler(){};
    private:
        can_frame frameGen;
        display dispHndl;
        dataLayer dataHndl;
        canHandler canHndl;
        uint16_t displayUpdateRate = 100;

};

#endif