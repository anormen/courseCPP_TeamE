#include "key_input_X11.hpp"
#include <iostream>

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