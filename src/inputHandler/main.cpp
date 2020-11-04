#include <iostream>
#include <curses.h>
#include "socketcan_cpp.h"
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

    scpp::CanFrame frame;
    canHandler can;
    can.canInit();

    //Conversion conv;

    while (1)
    {
        if ((key = getch()) == ERR)
        {
            // Do nothing
        } else {
            std::cout << "Input is " << key << std::endl;

            //Conv.SetKey(key)
            //Conv.GetFrame(&frame)
            can.canWriteFrame();
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
