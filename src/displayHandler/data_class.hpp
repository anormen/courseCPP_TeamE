#ifndef _DATA_CLASS_H_
#define _DATA_CLASS_H_

#include "display_class.hpp"
#include "frames.hpp"
#include "display_handler.hpp"

class dataLayer{

    public:
        dataLayer(){};
        void processInput(display &dHndl, const can_frame &frameGen);
        ~dataLayer(){};
    private:
        frame_100 fr100;
        frame_200 fr200;
        frame_300 fr300;
};

#endif