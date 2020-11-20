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
    unit16_t rpm = frm_200.get_rpm();
    frm_100.set_brake(0);
    frm_100.set_gearlever(fr::GearLeverPos::PARK);
    frm_200.set_rpm(0);
    frm_100.set_startstop(fr::StartButtonSts::UNPRESSED);  
    frm_100.set_mode(fr::SimulationMode::SLEEP);
    di.update(frm_100, rpm, info);
    //no message
    EXPECT_EQ( info, fr::DriverInformation::NO_MSG);
    frm_100.set_startstop(fr::StartButtonSts::PRESSED); 
    di.update(frm_100, rpm, info);
    //no message
    EXPECT_EQ( info, fr::DriverInformation::NO_MSG);
    //no key
    frm_100.set_mode(fr::SimulationMode::INACTIVE);
    frm_100.set_startstop(fr::StartButtonSts::PRESSED); 
    di.update(frm_100, rpm, info);
    EXPECT_EQ( info, fr::DriverInformation::NO_KEY);

};

