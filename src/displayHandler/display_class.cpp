#include "display_class.h"
#include <iostream>
#include <iomanip>
#include <stdint.h>

void displayHandler::initDisplay()
{

}

void displayHandler::update()
{
    std::cout << std::dec << std::setw(3) << std::setfill('0') << "Accelerator: " << (uint8_t)accelerator << " %" << std::endl;
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "Brake:       " << (uint8_t)brake << " %" << std::endl;
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "EngineSpeed: " << (uint16_t)rpm << " rpm" << std::endl;    
}