#include "display_class.h"
#include <iostream>
#include <iomanip>

void displayHandler::initDisplay()
{

}

void displayHandler::update()
{
    std::cout << std::dec << std::setw(3) << std::setfill('0') << "Accelerator: " << (int)accelerator << std::endl;
    std::cout << std::dec << std::setw(4) << std::setfill('0') << "Brake: " << (int)rpm << std::endl;
}