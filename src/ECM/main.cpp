#include <iostream>
#include "socketcan_cpp.h"
#include "ECM.hpp"

int main()
{

    int acc_ped = 0;
    bool engine_on = true;

    ECM ecm = ECM();
    for (size_t i = 1; i <= 100; i++)
    {
        ecm.CalculateRPM(acc_ped);
        std::cout << "RPM: " << ecm.GetRPM() << std::endl;
        if(i%20==0)
            acc_ped+=20;
    }

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
