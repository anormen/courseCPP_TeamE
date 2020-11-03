#include <iostream>
#include <X11/Xlib.h>
#include "socketcan_cpp.h"


uint ReadInputKey(Display *display, XEvent &event){
        
        uint key = 0;
        XNextEvent(display, &event);
 
        /* keyboard events */
        if (event.type == KeyPress)
        {
            printf( "KeyPress: %x\n", event.xkey.keycode );
            key = event.xkey.keycode;

            /* exit on ESC key press */
            //if ( event.xkey.keycode == 0x09 )
            //    break;
        }
        else if (event.type == KeyRelease)
        {
            //printf( "KeyRelease: %x\n", event.xkey.keycode );
        }
    return key;

}

void SetupKeyInput(Display *display, Window &window){

    int s;
    //display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }
 
    s = DefaultScreen(display);
 
    /* create window */
    window = XCreateSimpleWindow(display, RootWindow(display, s), 1, 1, 2, 2, 1,
                           BlackPixel(display, s), WhitePixel(display, s));
 
    /* select kind of events we are interested in */
    XSelectInput(display, window, KeyPressMask | KeyReleaseMask );
 
    /* map (show) the window */
    XMapWindow(display, window);
}

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

    */
    
   /*

    clear memory
    */

    //First version with pseudo code
}
