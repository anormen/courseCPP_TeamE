
#include <gtest/gtest.h>
#include "frames.hpp"
#include "../src/ECM/driverInfo.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <stdint.h>

class driverInfoTest : public testing::Test
{

protected:
    fr::GearLeverPos gear_lever;
    fr::StartButtonSts start_stop;
    uint16_t rpm;
    fr::SimulationMode mode;
    uint8_t brake;
    driverInfo di;
    virtual void SetUp()
    {
        gear_lever = fr::GearLeverPos::PARK;
        start_stop = fr::StartButtonSts::UNPRESSED;
        rpm = 0;
        mode = fr::SimulationMode::INACTIVE;
        brake = 0;
    }
    virtual void TearDown()
    {
        // Code here will be called immediately after each test
        // (right before the destructor).
    }
};

TEST_F(driverInfoTest, driverinfoMessagesNone)
{

    mode = fr::SimulationMode::SLEEP;
    start_stop = fr::StartButtonSts::PRESSED;
    EXPECT_EQ(di.update(start_stop, mode, rpm, brake, gear_lever), fr::DriverInformation::NO_MSG);

    brake = 10;
    gear_lever = fr::GearLeverPos::PARK;
    mode = fr::SimulationMode::ACTIVE;
    //no message
    EXPECT_EQ(di.update(start_stop, mode, rpm, brake, gear_lever), fr::DriverInformation::NO_MSG);

    //park and running
    brake = 0;
    rpm = 1000;
    EXPECT_EQ(di.update(start_stop, mode, rpm, brake, gear_lever), fr::DriverInformation::NO_MSG);
}

TEST_F(driverInfoTest, driverinfoMessagesKey)
{
    mode = fr::SimulationMode::INACTIVE;
    start_stop = fr::StartButtonSts::PRESSED;
    EXPECT_EQ(di.update(start_stop, mode, rpm, brake, gear_lever), fr::DriverInformation::NO_KEY);
}
TEST_F(driverInfoTest, driverinfoMessagesBrake)
{
    brake = 0;
    mode = fr::SimulationMode::ACTIVE;
    start_stop = fr::StartButtonSts::PRESSED;
    EXPECT_EQ(di.update(start_stop, mode, rpm, brake, gear_lever), fr::DriverInformation::NO_BRAKE);

    gear_lever = fr::GearLeverPos::NEUTRAL;
    EXPECT_EQ(di.update(start_stop, mode, rpm, brake, gear_lever), fr::DriverInformation::NO_BRAKE);
}
TEST_F(driverInfoTest, driverinfoMessagesNotInP)
{
    mode = fr::SimulationMode::ACTIVE;
    start_stop = fr::StartButtonSts::PRESSED;
    gear_lever = fr::GearLeverPos::NEUTRAL;
    brake = 10;
    EXPECT_EQ(di.update(start_stop, mode, rpm, brake, gear_lever), fr::DriverInformation::NOT_IN_P);
}
TEST_F(driverInfoTest, driverinfoMessagesNotInPInD)
{
    //drive and running
    mode = fr::SimulationMode::ACTIVE;
    start_stop = fr::StartButtonSts::PRESSED;
    gear_lever = fr::GearLeverPos::DRIVE;
    rpm = 1000;
    EXPECT_EQ(di.update(start_stop, mode, rpm, brake, gear_lever), fr::DriverInformation::NOT_IN_P_IN_D);
}

TEST_F(driverInfoTest, driverinfoMessagesGetInfo)
{
    mode = fr::SimulationMode::ACTIVE;
    start_stop = fr::StartButtonSts::PRESSED;
    gear_lever = fr::GearLeverPos::NEUTRAL;
    brake = 10;
    di.update(start_stop, mode, rpm, brake, gear_lever);
    EXPECT_EQ(di.getInfoMsg(), fr::DriverInformation::NOT_IN_P);
}
TEST_F(driverInfoTest, driverinfoMessagesTimer)
{
    mode = fr::SimulationMode::ACTIVE;
    start_stop = fr::StartButtonSts::PRESSED;
    gear_lever = fr::GearLeverPos::PARK;
    brake = 0;
    di.update(start_stop, mode, rpm, brake, gear_lever);
    EXPECT_EQ(di.getInfoMsg(), fr::DriverInformation::NO_BRAKE);

    start_stop = fr::StartButtonSts::UNPRESSED;
    di.update(start_stop, mode, rpm, brake, gear_lever);

    std::this_thread::sleep_for(std::chrono::milliseconds(1250));

    di.update(start_stop, mode, rpm, brake, gear_lever);
    EXPECT_EQ(di.getInfoMsg(), fr::DriverInformation::NO_BRAKE);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    di.update(start_stop, mode, rpm, brake, gear_lever);
    EXPECT_EQ(di.getInfoMsg(), fr::DriverInformation::NO_MSG);
}

int main(int argc, char **argv)
{

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}