#include <iostream>
#include <curses.h>
#include "can_class.h"
#include "frames.hpp"

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
    fr100 fr100_to_send;
    //memset(&fr100_to_send,0,sizeof(fr100_to_send));
    fr100_to_send.accelerator=0;
    fr100_to_send.startstop=0;
    fr100_to_send.brake=0;

    while (1)
    {
        if ((key = getch()) == ERR)
        {
            // Do nothing
        } else {
            std::cout << "Input is " << key << std::endl;

            if(key==259)
                fr100_to_send.accelerator+=10;

            if(key==115)
                fr100_to_send.startstop=!fr100_to_send.startstop; // toggle bit, does this work?

            //std::cout << "&data_to_send = " << &data_to_send << " &data_to_send+6 " << &data_to_send+6 << std::endl;

            memcpy(&frame,&fr100_to_send,16);

            //std::cout << "frame->data[0] = " << (int)frame->data[0] << std::endl;

            uint16_t b = can.canWriteFrame(frame);
            std::cout << "b = " << b << std::endl;
        }
    }

    return 0;

}
