#include <iostream>
#include "socketcan_cpp.h"
#include "key_input_X11.hpp"

int main() {

    std::cout << "inputHandler\n";

    Display *display;
    Window window;
    XEvent event;
    uint key;
    display = XOpenDisplay(NULL);

    SetupKeyInput(display,window);
    
    while(1){
        key = ReadInputKey(display,event);
        std::cout << "key = " << key << std::endl;
    }

    XCloseDisplay(display);
    return 0;
    /*
    Init:
        X11
        CAN

    while{
        read input key
        convert key->can.data 
            arrow_up -> acc_ped +10%   can_frame.data[0]
            arrow_down -> acc_ped -10%  can_frame.data[0]
            s -> engine start/stop can_frame.data[1]
            frame id = 100
        send can message
        sleep
    }

    clear memory
    */

}
