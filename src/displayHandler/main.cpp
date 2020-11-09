
#include <chrono>
#include <thread>  
#include "can_class.h"
#include "display_class.h"
#include "display_handler.hpp"
#include "frames.hpp"

int main()
{
    displayHandler disp;

    while(1){
        disp.run();
    }
    return 0;
}
