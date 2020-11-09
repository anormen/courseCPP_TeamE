#ifndef _DATA_CLASS_H_
#define _DATA_CLASS_H_

#include "display_class.hpp"
#include "frames.hpp"
#include "display_handler.hpp"

class dataLayer{

    public:
        dataLayer(){};
        void process(display &dhndl, const can_frame &frameGen);
        ~dataLayer(){};
    private:
        fr100 frame100;
        fr200 frame200;
        fr300 frame300;
};

#endif