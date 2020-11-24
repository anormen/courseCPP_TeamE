#include <gtest/gtest.h>
#include "frames.hpp"
#include "../src/ECM/driverInfo.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <stdint.h>

class driverInfoTest : public testing::Test {

	 protected:
        fr::frame_100 data; 
        driverInfo di;
	  virtual void SetUp() {
            data.set_brake(0);
            data.set_gearlever(fr::GearLeverPos::PARK);
            data.set_startstop(fr::StartButtonSts::UNPRESSED);  
            data.set_mode(fr::SimulationMode::SLEEP);            
	  }
	  virtual void TearDown() {
	    // Code here will be called immediately after each test
	    // (right before the destructor).
	  }
};

TEST_F(driverInfoTest, driverinfoMessagesNone){
    
    data.set_mode(fr::SimulationMode::SLEEP); 
    data.set_startstop(fr::StartButtonSts::PRESSED);      
    EXPECT_EQ( di.update(data, 0), fr::DriverInformation::NO_MSG);

    data.set_brake(10);
    data.set_gearlever(fr::GearLeverPos::PARK);   
    data.set_mode(fr::SimulationMode::ACTIVE);      
    //no message
    EXPECT_EQ( di.update(data, 0), fr::DriverInformation::NO_MSG);

    //park and running 
    data.set_brake(0);  
    EXPECT_EQ( di.update(data, 1000), fr::DriverInformation::NO_MSG); 
}

TEST_F(driverInfoTest, driverinfoMessagesKey)
{    
    data.set_mode(fr::SimulationMode::INACTIVE);
    data.set_startstop(fr::StartButtonSts::PRESSED); 
    EXPECT_EQ( di.update(data, 0), fr::DriverInformation::NO_KEY);
}
TEST_F(driverInfoTest, driverinfoMessagesBrake)
{
    data.set_brake(0);
    data.set_mode(fr::SimulationMode::ACTIVE);
    data.set_startstop(fr::StartButtonSts::PRESSED); 
    EXPECT_EQ( di.update(data, 0), fr::DriverInformation::NO_BRAKE);

    data.set_gearlever(fr::GearLeverPos::NEUTRAL);    
    EXPECT_EQ( di.update(data, 0), fr::DriverInformation::NO_BRAKE);   
}
TEST_F(driverInfoTest, driverinfoMessagesNotInP)
{ 
    data.set_mode(fr::SimulationMode::ACTIVE);
    data.set_startstop(fr::StartButtonSts::PRESSED); 
    data.set_gearlever(fr::GearLeverPos::NEUTRAL);   
    data.set_brake(10); 
    EXPECT_EQ( di.update(data, 0), fr::DriverInformation::NOT_IN_P);   
}
TEST_F(driverInfoTest, driverinfoMessagesNotInPInD)
{ 
    //drive and running
    data.set_mode(fr::SimulationMode::ACTIVE);
    data.set_startstop(fr::StartButtonSts::PRESSED); 
    data.set_gearlever(fr::GearLeverPos::DRIVE);     
    EXPECT_EQ( di.update(data, 1000), fr::DriverInformation::NOT_IN_P_IN_D);    
}

TEST_F(driverInfoTest, driverinfoMessagesGetInfo)
{ 
    data.set_mode(fr::SimulationMode::ACTIVE);
    data.set_startstop(fr::StartButtonSts::PRESSED); 
    data.set_gearlever(fr::GearLeverPos::NEUTRAL);   
    data.set_brake(10);   
    di.update(data, 0); 
    EXPECT_EQ( di.getInfoMsg(), fr::DriverInformation::NOT_IN_P);  
       
}
TEST_F(driverInfoTest, driverinfoMessagesTimer)
{ 
    data.set_mode(fr::SimulationMode::ACTIVE);
    data.set_startstop(fr::StartButtonSts::PRESSED); 
    data.set_gearlever(fr::GearLeverPos::PARK);   
    data.set_brake(0);   
    di.update(data, 0); 
    EXPECT_EQ( di.getInfoMsg(), fr::DriverInformation::NO_BRAKE);  

    data.set_startstop(fr::StartButtonSts::UNPRESSED);  
    di.update(data, 0);  

    std::this_thread::sleep_for(std::chrono::milliseconds(1250));

    di.update(data, 0); 
    EXPECT_EQ( di.getInfoMsg(), fr::DriverInformation::NO_BRAKE); 

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    di.update(data, 0);  
    EXPECT_EQ( di.getInfoMsg(), fr::DriverInformation::NO_MSG);        
}

int main (int argc, char **argv){

    ::testing::InitGoogleTest(&argc, argv);

    return  RUN_ALL_TESTS();
}