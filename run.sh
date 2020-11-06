#!/bin/sh
x-terminal-emulator -T Display -e ./build/displayHandler
x-terminal-emulator -T ECM -e ./build/ECM
#x-terminal-emulator -T TCM -e ./build/TCM
x-terminal-emulator -T Input -e ./build/inputHandler
