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


int main (int argc, char **argv){

    ::testing::InitGoogleTest(&argc, argv);

    return  RUN_ALL_TESTS();
}