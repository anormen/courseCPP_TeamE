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
    std::cout << "\033c \033[0;32m" ;  //http://ascii-table.com/ansi-escape-sequences.php
    std::cout << "----------------------------------------------------------------" << std::endl;    
    std::cout << std::dec << std::setw(3) << std::setfill('0') << "Accelerator:     " << (int)accelerator   << " %" << std::endl;
    std::cout << std::dec << std::setw(3) << std::setfill('0') << "Brake:           " << (int)brake         << " %" << std::endl;
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "EngineSpeed:     " << (int)rpm           << " rpm" << std::endl;    
    std::cout << std::dec << std::setw(2) << std::setfill('0') << "Mode:            " << modes.at((uint8_t)mode) << "" << std::endl; 
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "StartStop:       " << (int)startstop     << " " << std::endl; 
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "GearLever:       " << gears.at((uint8_t)gearlever) << "" << std::endl; 
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "GearActual:      " << (int)gearactual    << "" << std::endl;  
    std::cout << std::dec << std::setw(2) << std::setfill('0') << "GearRatio:       " << (int)gearratio    << "" << std::endl;  
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "VehicleSpeed:    " << (int)vehiclespeed  << " km/h" << std::endl; 
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "DriverInfo msg   " << messages.at((uint8_t)driverinfo) << "" << std::endl;     
    std::cout << std::dec << std::setw(2) << std::setfill('0') << "Telltale:        " << telltales.at((uint8_t)telltale) << "" << std::endl;     
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "Avg Fuel con:    " << (float)fuelconsumavg << " l/100km" << std::endl;    
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "Inst Fuel con:   " << (float)fuelconsuminst << " l/h" << std::endl;      
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "Input UB:        " << (int)inputUb       << " " << std::endl; 
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "ECM UB:          " << (int)ecmUb         << " " << std::endl;     
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "TCM UB:          " << (int)tcmUb         << " " << std::endl; 
    std::cout << "----------------------------------------------------------------" << std::endl;
}

void display::updateTelltale(){

    if(updateTimeout > fr100_updateRate *3 && inputUb == 0)
        telltale = Telltale::INPUT;
    else if (updateTimeout > fr100_updateRate *3 && ecmUb == 0)
        telltale = Telltale::ECM;
    else if (updateTimeout > fr100_updateRate *3 && tcmUb == 0)
        telltale = Telltale::TCM;
    else
        telltale = Telltale::PRESENT;

    //evaluate and zero
    if(inputUb && ecmUb && tcmUb)
        updateTimeout = 0;
    else
        updateTimeout += fr100_updateRate * 3;
}