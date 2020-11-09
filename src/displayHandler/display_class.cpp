#include "display_class.hpp"
#include <iostream>
#include <iomanip>
#include <stdint.h>

void display::initDisplay()
{
    std::cout << "Starting display handler..." << std::endl; //do something if needed
}

void display::update()
{ 
    std::cout << std::dec << std::setw(3) << std::setfill('0') << "Accelerator:     " << (int)accelerator << " %" << std::endl;
    std::cout << std::dec << std::setw(3) << std::setfill('0') << "Brake:           " << (int)brake << " %" << std::endl;
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "EngineSpeed:     " << (int)rpm << " rpm" << std::endl;    
    std::cout << std::dec << std::setw(2) << std::setfill('0') << "Mode:            " << (int)mode << " " << std::endl; 
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "StartStop:       " << (int)startstop << " " << std::endl; 
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "GearLever:       " << (int)gearlever << " " << std::endl; 
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "GearActual:      " << (int)gearactual << " " << std::endl;  
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "VehicleSpeed:    " << (int)vehiclespeed << " km/h " << std::endl; 
    std::cout << std::dec << std::setw(2) << std::setfill('0') << "Telltale:        " << (int)telltale << " " << std::endl;     
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "Avg Fuel con:    " << (int)fuelconsumption << " l/100km " << std::endl;    
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "Input ub:        " << (int)inputUb << " " << std::endl; 
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "ECM ub:          " << (int)ecmUb << " " << std::endl;     
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "TCM ub:          " << (int)tcmUb << " " << std::endl; 
}