#include <iostream>
#include <curses.h>
#include "socketcan_cpp.h"

int main()
{

    std::cout << "inputHandler\n";
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int ch;
    nodelay(stdscr, TRUE);

    while (1)
    {
        if ((ch = getch()) == ERR)
        {
            // Do nothing
        } else {
            std::cout << "Input is " << ch << std::endl;
            // Call convert (check if valid?)
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
