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
    updateTelltale();
    std::cout << "----------------------------------------------------------------" << std::endl;    
    std::cout << std::dec << std::setw(3) << std::setfill('0') << "Accelerator:     " << (int)accelerator   << " %" << std::endl;
    std::cout << std::dec << std::setw(3) << std::setfill('0') << "Brake:           " << (int)brake         << " %" << std::endl;
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "EngineSpeed:     " << (int)rpm           << " rpm" << std::endl;    
    std::cout << std::dec << std::setw(2) << std::setfill('0') << "Mode:            " << modes.at((uint8_t)mode) << "" << std::endl; 
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "StartStop:       " << (int)startstop     << " " << std::endl; 
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "GearLever:       " << gears.at((uint8_t)gearlever) << "" << std::endl; 
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "GearActual:      " << (int)gearactual    << "" << std::endl;  
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "VehicleSpeed:    " << (int)vehiclespeed  << " km/h" << std::endl; 
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "DriverInfo msg   " << messages.at((uint8_t)driverinfo) << "" << std::endl;     
    std::cout << std::dec << std::setw(2) << std::setfill('0') << "Telltale:        " << telltales.at((uint8_t)telltale) << "" << std::endl;     
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "Avg Fuel con:    " << (float)fuelconsumavg / 100.0 << " l/100km" << std::endl;    
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "Inst Fuel con:   " << (float)fuelconsuminst / 100.0 << " l/h" << std::endl;      
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "Input UB:        " << (int)inputUb       << " " << std::endl; 
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "ECM UB:          " << (int)ecmUb         << " " << std::endl;     
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "TCM UB:          " << (int)tcmUb         << " " << std::endl; 
    std::cout << "----------------------------------------------------------------" << std::endl;
}

void display::updateTelltale(){

    if(!inputUb)
        telltale = (uint8_t)Telltale::INPUT;
    else if (!ecmUb)
        telltale = (uint8_t)Telltale::ECM;
    else if (!tcmUb)
        telltale = (uint8_t)Telltale::TCM;
    else
        telltale = (uint8_t)Telltale::PRESENT;
}