#include "display_class.h"
#include <iostream>
#include <iomanip>
#include <stdint.h>

void displayHandler::initDisplay()
{

}

void displayHandler::update()
{
    std::cout << std::dec << std::setw(3) << std::setfill('0') << "Accelerator:     " << (int)accelerator << " %" << std::endl;
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "Brake:           " << (int)brake << " %" << std::endl;
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "EngineSpeed:     " << (int)rpm << " rpm" << std::endl;    
    std::cout << std::dec << std::setw(2) << "Mode:        " << (int)mode << " " << std::endl; 
    std::cout << std::dec << std::setw(1) << "StartStop:   " << (int)startstop << " " << std::endl; 
    std::cout << std::dec << std::setw(2) << "GearLever:   " << (int)gearlever << " " << std::endl; 
    std::cout << std::dec << std::setw(1) << "GearActual:  " << (int)gearactual << " " << std::endl;  
    std::cout << std::dec << std::setw(3) << "VehicleSpeed:" << (int)vehiclespeed << " km/h " << std::endl; 
    std::cout << std::dec << std::setw(2) << "Telltale:    " << (int)telltale << " " << std::endl;     
    std::cout << std::dec << std::setw(3) << "Avg Fuel con:" << (int)fuelconsumption << " l/100km " << std::endl;    
    std::cout << std::dec << std::setw(1) << "Input ub:    " << (int)inputUb << " " << std::endl; 
    std::cout << std::dec << std::setw(1) << "ECM ub:      " << (int)ecmUb << " " << std::endl;     
    std::cout << std::dec << std::setw(1) << "TCM ub:      " << (int)tcmUb << " " << std::endl; 
}