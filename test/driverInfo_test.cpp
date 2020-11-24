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
    
    void SetUp()// override
    {
        //frm_100.set_accelerator(20);
    }
};

TEST_F(FrameFixture, driverinfoMessages)
{
    driverInfo di;
    fr::DriverInformation info = fr::DriverInformation::NO_MSG;
    uint16_t rpm = 0;
    frm_100.set_brake(0);
    frm_100.set_gearlever(fr::GearLeverPos::PARK);


    frm_100.set_startstop(fr::StartButtonSts::UNPRESSED);  
    frm_100.set_mode(fr::SimulationMode::SLEEP);

    di.update(frm_100, rpm);
    //no message
    EXPECT_EQ( info, fr::DriverInformation::NO_MSG);
    frm_100.set_startstop(fr::StartButtonSts::PRESSED); 
    di.update(frm_100, rpm);
    //no message
    EXPECT_EQ( info, fr::DriverInformation::NO_MSG);
    //no key
    frm_100.set_mode(fr::SimulationMode::INACTIVE);
    frm_100.set_startstop(fr::StartButtonSts::PRESSED); 
    di.update(frm_100, rpm);
    EXPECT_EQ( info, fr::DriverInformation::NO_KEY);

    //no brake
    frm_100.set_mode(fr::SimulationMode::ACTIVE);
    frm_100.set_startstop(fr::StartButtonSts::PRESSED); 
    di.update(frm_100, rpm);
    EXPECT_EQ( info, fr::DriverInformation::NO_BRAKE);
    //no brake
    frm_100.set_mode(fr::SimulationMode::ACTIVE);
    frm_100.set_startstop(fr::StartButtonSts::PRESSED); 
    frm_100.set_gearlever(fr::GearLeverPos::NEUTRAL);    
    di.update(frm_100, rpm);
    EXPECT_EQ( info, fr::DriverInformation::NO_BRAKE);    
    //no brake and neutral
    frm_100.set_mode(fr::SimulationMode::ACTIVE);
    frm_100.set_startstop(fr::StartButtonSts::PRESSED); 
    frm_100.set_gearlever(fr::GearLeverPos::NEUTRAL);   
    frm_100.set_brake(10); 
    di.update(frm_100, rpm);
    EXPECT_EQ( info, fr::DriverInformation::NOT_IN_P);   

    //no brake and park
    frm_100.set_mode(fr::SimulationMode::ACTIVE);
    frm_100.set_startstop(fr::StartButtonSts::PRESSED); 
    frm_100.set_gearlever(fr::GearLeverPos::PARK);   
    frm_100.set_brake(10); 
    di.update(frm_100, rpm);
    EXPECT_EQ( info, fr::DriverInformation::NO_MSG);

    //drive and running
    frm_100.set_mode(fr::SimulationMode::ACTIVE);
    frm_100.set_startstop(fr::StartButtonSts::PRESSED); 
    frm_100.set_gearlever(fr::GearLeverPos::DRIVE);   
    frm_100.set_brake(10); 
    rpm = 1000;    
    di.update(frm_100, rpm);
    EXPECT_EQ( info, fr::DriverInformation::NOT_IN_P_IN_D);    

    //park and running
    frm_100.set_mode(fr::SimulationMode::ACTIVE);
    frm_100.set_startstop(fr::StartButtonSts::PRESSED); 
    frm_100.set_gearlever(fr::GearLeverPos::PARK);   
    frm_100.set_brake(10); 
    rpm = 1000;    
    di.update(frm_100, rpm);
    EXPECT_EQ( info, fr::DriverInformation::NO_MSG);                

}

int main (int argc, char **argv){

    ::testing::InitGoogleTest(&argc, argv);

    return  RUN_ALL_TESTS();
}

