#include <iostream>
#include "socketcan_cpp.h"
#include "ECM.hpp"

int main() {

    /*

    Init:
        CAN read
        CAN write
        ECM class

    while( 
        (should be two seperate threads later)
        Read CAN
        convert from can_frame.data
        calc RPM
        convert to can_frame.data
        Write CAN
    )

    clear memory etc
    */
    std::cout << "ECM main\n";
    //First version with pseudo code
}
