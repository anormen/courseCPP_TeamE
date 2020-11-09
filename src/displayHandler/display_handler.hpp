#ifndef _DISPLAY_HANDLER_H_
#define _DISPLAY_HANDLER_H_

#include "display_class.hpp"
#include "frames.hpp"
#include "can_class.h"
#include "data_class.hpp"

class displayHandler{

    public:
        displayHandler();
        bool getValue_isRunning() { return isRunning; };
        void setValue_isRunning(bool _isRunning){ isRunning = _isRunning; };    
        void run();
        ~displayHandler(){};
    private:
        bool isRunning = true;
        can_frame frameGen;
        display dispHndl;
        dataLayer dataHndl;
        canHandler canHndl;
        uint16_t displayUpdateRate = 100;
};

#endif