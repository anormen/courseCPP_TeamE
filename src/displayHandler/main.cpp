#include <thread>  
#include "display_handler.hpp"
#include "display_class.hpp"
#include "data_class.hpp"
#include "frames.hpp"

int main()
{
    displayHandler disp;

    while(disp.run()){
        //do someting if needed
    };

    return 0;
}