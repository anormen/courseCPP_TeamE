#include <gtest/gtest.h>
#include "frames.hpp"
#include "../src/ECM/driverInfo.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>

class FrameFixture : public ::testing::Test {
  protected:
    // NOLINTNEXTLINE
    fr::frame_100 frm_100;
    fr::frame_200 frm_200;
    fr::frame_300 frm_300;        
    
    fr::GearLeverPos gear_lever = fr::GearLeverPos::PARK;
    fr::StartButtonSts start_stop = fr::StartButtonSts::UNPRESSED;
    uint16_t rpm = 0;
    fr::SimulationMode mode = fr::SimulationMode::INACTIVE;
    uint8_t brake = 0;

    void SetUp()// override
    {
        //frm_100.set_accelerator(20);
    }
};

TEST_F(FrameFixture, driverinfoMessages)
{
    driverInfo di;
    fr::DriverInformation info = fr::DriverInformation::NO_MSG;
    rpm = 0;
    brake = 0;
    gear_lever = fr::GearLeverPos::PARK;
    start_stop = fr::StartButtonSts::UNPRESSED; 
    mode =fr::SimulationMode::SLEEP;

    info = di.update(start_stop, mode, rpm, brake, gear_lever);
    //no message
    EXPECT_EQ( info, fr::DriverInformation::NO_MSG);
    start_stop = fr::StartButtonSts::PRESSED; 
    info = di.update(start_stop, mode, rpm, brake, gear_lever);
    //no message
    EXPECT_EQ( info, fr::DriverInformation::NO_MSG);
    //no key
    mode = fr::SimulationMode::INACTIVE;
    start_stop = fr::StartButtonSts::PRESSED; 
    info = di.update(start_stop, mode, rpm, brake, gear_lever);
    EXPECT_EQ( info, fr::DriverInformation::NO_KEY);

    //no brake
    mode = fr::SimulationMode::ACTIVE;
    start_stop = fr::StartButtonSts::PRESSED; 
    info = di.update(start_stop, mode, rpm, brake, gear_lever);
    EXPECT_EQ( info, fr::DriverInformation::NO_BRAKE);
    //no brake
    mode = fr::SimulationMode::ACTIVE;
    start_stop = fr::StartButtonSts::PRESSED; 
    gear_lever = fr::GearLeverPos::NEUTRAL;    
    info = di.update(start_stop, mode, rpm, brake, gear_lever);
    EXPECT_EQ( info, fr::DriverInformation::NO_BRAKE);    
    //no brake and neutral
    mode = fr::SimulationMode::ACTIVE;
    start_stop = fr::StartButtonSts::PRESSED;
    gear_lever = fr::GearLeverPos::NEUTRAL;   
    brake = 10;
    info = di.update(start_stop, mode, rpm, brake, gear_lever);
    EXPECT_EQ( info, fr::DriverInformation::NOT_IN_P);   

    //no brake and park
    mode = fr::SimulationMode::ACTIVE;
    start_stop = fr::StartButtonSts::PRESSED; 
    gear_lever = fr::GearLeverPos::PARK;   
    brake = 10; 
    info = di.update(start_stop, mode, rpm, brake, gear_lever);
    EXPECT_EQ( info, fr::DriverInformation::NO_MSG);

    //drive and running
    mode = fr::SimulationMode::ACTIVE;
    start_stop = fr::StartButtonSts::PRESSED; 
    gear_lever = fr::GearLeverPos::DRIVE;
    brake= 10; 
    rpm = 1000;    
    info = di.update(start_stop, mode, rpm, brake, gear_lever);
    EXPECT_EQ( info, fr::DriverInformation::NOT_IN_P_IN_D);    

    //park and running
    mode = fr::SimulationMode::ACTIVE;
    start_stop = fr::StartButtonSts::PRESSED;
    gear_lever = fr::GearLeverPos::PARK;
    brake = 10; 
    rpm = 1000;    
    info = di.update(start_stop, mode, rpm, brake, gear_lever);
    EXPECT_EQ( info, fr::DriverInformation::NO_MSG);                

}

int main (int argc, char **argv){

    ::testing::InitGoogleTest(&argc, argv);

    return  RUN_ALL_TESTS();
}

