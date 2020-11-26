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
    std::cout << "\033c \033[0;32m" ;  //http://ascii-table.com/ansi-escape-sequences.php
    std::cout << "----------------------------------------------------------------" << std::endl;    
    std::cout << std::dec << std::setw(3) << std::setfill('0') << "Accelerator:     " << static_cast<unsigned int>(accelerator)   << " %" << std::endl;
    std::cout << std::dec << std::setw(3) << std::setfill('0') << "Brake:           " << static_cast<unsigned int>(brake)         << " %" << std::endl;
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "EngineSpeed:     " << static_cast<unsigned int>(rpm)           << " rpm" << std::endl;    
    std::cout << std::dec << std::setw(2) << std::setfill('0') << "Mode:            " << fr::modes.at(static_cast<uint8_t>(mode)) << "" << std::endl; 
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "StartStop:       " << static_cast<unsigned int>(startstop)     << " " << std::endl; 
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "GearLever:       " << fr::gears.at(static_cast<uint8_t>(gearlever)) << "" << std::endl; 
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "GearActual:      " << static_cast<unsigned int>(gearactual)    << "" << std::endl;  
    std::cout << std::dec << std::setw(2) << std::setfill('0') << "GearRatio:       " << static_cast<unsigned int>(gearratio)    << "" << std::endl;  
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "VehicleSpeed:    " << static_cast<unsigned int>(vehiclespeed)  << " km/h" << std::endl; 
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "DriverInfo msg   " << fr::messages.at(static_cast<uint8_t>(driverinfo)) << "" << std::endl;     
    std::cout << std::dec << std::setw(2) << std::setfill('0') << "Telltale:        " << fr::telltales.at(static_cast<uint8_t>(telltale)) << "" << std::endl;     
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "Avg Fuel con:    " << static_cast<float>(fuelconsumavg) << " l/100km" << std::endl;    
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "Inst Fuel con:   " << static_cast<float>(fuelconsuminst) << " l/h" << std::endl;      
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "Input UB:        " << static_cast<bool>(inputUb)       << " " << std::endl; 
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "ECM UB:          " << static_cast<bool>(ecmUb)         << " " << std::endl;     
    std::cout << std::dec << std::setw(1) << std::setfill('0') << "TCM UB:          " << static_cast<bool>(tcmUb)         << " " << std::endl; 
    std::cout << "----------------------------------------------------------------" << std::endl;
    updateTelltale();    
}

void display::updateTelltale(){

    if(!inputUb)
        telltale = fr::Telltale::INPUT;
    else if(!ecmUb)
        telltale = fr::Telltale::ECM;
    else if(!tcmUb)
        telltale = fr::Telltale::TCM;                        
    else
        telltale = fr::Telltale::PRESENT;

    ecmUb=0; tcmUb=0; inputUb=0;
}