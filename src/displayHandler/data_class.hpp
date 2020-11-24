#ifndef _DATA_CLASS_H_
#define _DATA_CLASS_H_

#include "display_class.hpp"
#include "frames.hpp"
#include "display_handler.hpp"

namespace fr=frames;

class dataLayer{

    public:
        dataLayer(){}
        void processInput(display &dHndl, const can_frame &frameGen);
        ~dataLayer(){}
    private:
};

#endif