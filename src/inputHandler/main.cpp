#include <iostream>
#include <curses.h>
#include "can_class.h"

int main()
{

    std::cout << "inputHandler\n";
    // Init key input
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int key;
    nodelay(stdscr, TRUE);

    can_frame *frame;
    canHandler can;
    can.canInit();

    frame=can.getTxBuffer();
    frame->can_dlc=1;
    frame->data[0]=0;
    frame->can_id=100;

    //Conversion conv;

    while (1)
    {
        if ((key = getch()) == ERR)
        {
            // Do nothing
        } else {
            std::cout << "Input is " << key << std::endl;

            if(key==259)
                frame->data[0]+=10;

            std::cout << "frame->data[0] = " << (int)frame->data[0] << std::endl;

            uint16_t b = can.canWriteFrame();
            std::cout << "b = " << b << std::endl;
        }
    }

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
