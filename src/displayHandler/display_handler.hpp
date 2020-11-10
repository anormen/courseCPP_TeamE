#ifndef _DISPLAY_HANDLER_H_
#define _DISPLAY_HANDLER_H_

#include "display_class.hpp"
#include "frames.hpp"
#include "can_class.h"
#include "data_class.hpp"
#include <future>

class displayHandler{

    public:
        displayHandler();
        bool run();
        ~displayHandler(){};
    private:
        std::promise<void> finishedReader, finishedDisplay;
        std::future<void> futureReader, futureDisplay;
        can_frame frameGen;
        display dispHndl;
        dataLayer dataHndl;
        canHandler canHndl;
        uint16_t displayUpdateRate = 500;
};

#endif