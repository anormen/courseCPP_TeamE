#include <gtest/gtest.h>
#include "../share/frames.hpp"
#include <iostream>
#include <vector>
#include "../src/TCM/gearbox.hpp"

using namespace frames;

class FrameFixture : public ::testing::Test {
  
    public:
    Gearbox gb;
    uint8_t acc = 0;
    int engRpm = 0;
    GearLeverPos gearleverpostion = GearLeverPos::PARK;

  protected:
    

    void SetUp() override
    {
        acc = 0;
        engRpm = 0;
        gearleverpostion = GearLeverPos::PARK;

        for (int i = 0; i<5000; i++)
        {
            gb.setGearleverPos(gearleverpostion); 
            gb.selectGear(acc, engRpm);
            gb.calculateVehicleSpeed(acc, engRpm, gearleverpostion);

        }
    }
};

TEST_F(FrameFixture, test_park_speed)
{
    acc = 0;
    engRpm = 900;
    gearleverpostion = GearLeverPos::PARK;

for (int i = 0; i<5000; i++)
{
    gb.setGearleverPos(gearleverpostion); 
    gb.selectGear(acc, engRpm);
    gb.calculateVehicleSpeed(acc, engRpm, gearleverpostion);

}
acc = 20;
engRpm = 3000;

for (int i = 0; i<5000; i++)
{
    gb.setGearleverPos(gearleverpostion); 
    gb.selectGear(acc, engRpm);
    gb.calculateVehicleSpeed(acc, engRpm, gearleverpostion);

}
    
    EXPECT_EQ(gb.getVehicleSpeed() ,0);
    
};


TEST_F(FrameFixture, test_park_gear)
{
    
    acc = 0;
    engRpm = 900;
    gearleverpostion = GearLeverPos::PARK;

for (int i = 0; i<5000; i++)
{
    gb.setGearleverPos(gearleverpostion); 
    gb.selectGear(acc, engRpm);
    gb.calculateVehicleSpeed(acc, engRpm, gearleverpostion);

}
acc = 20;
engRpm = 3000;

for (int i = 0; i<5000; i++)
{
    gb.setGearleverPos(gearleverpostion); 
    gb.selectGear(acc, engRpm);
    gb.calculateVehicleSpeed(acc, engRpm, gearleverpostion);

}
    
    EXPECT_EQ(gb.getGear() ,1);
};

