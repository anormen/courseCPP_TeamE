#include <iostream>
#include <curses.h>
#include "can_class.h"
#include "frames.hpp"
#include<bitset>

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

    can_frame frame;
    canHandler can;
    can.canInit();

    uint8_t a;
    fr100 data_to_send;
    //data_to_send.acc_ped=0;

    //frame=can.getTxBuffer();
    data_to_send.accelerator=0;

    while (1)
    {
        if ((key = getch()) == ERR)
        {
            // Do nothing
        } else {
            std::cout << "Input is " << key << std::endl;

            if(key==259)
                data_to_send.accelerator+=10;

            if(key==115)
                data_to_send.startstop=!data_to_send.startstop; // toggle bit, does this work?

            //std::cout << "&data_to_send = " << &data_to_send << " &data_to_send+6 " << &data_to_send+6 << std::endl;

            memcpy(&frame,&data_to_send,16);

            //std::cout << "frame->data[0] = " << (int)frame->data[0] << std::endl;

            uint16_t b = can.canWriteFrame(frame);
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
