#ifndef KEY_INPUT_HPP
#define KEY_INPUT_HPP

#include <X11/Xlib.h>

uint ReadInputKey(Display *display, XEvent &event);

void SetupKeyInput(Display *display, Window &window);

#endif