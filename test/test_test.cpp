#include <gtest/gtest.h>
#include "frames.hpp"
#include <iostream>
#include <vector>

namespace fr=frames;

class FrameFixture : public ::testing::Test {
  protected:
    // NOLINTNEXTLINE
    fr::frame_100 frm_100;
    

    void SetUp() override
    {
        //frm_100.set_accelerator(20);
    }
};

TEST_F(FrameFixture, test_acc)
{
    uint8_t acc = 20;
    frm_100.set_accelerator(acc);
    EXPECT_EQ(frm_100.get_accelerator(),acc);
};

TEST_F(FrameFixture, test_acc_fail)
{
    uint8_t acc = 20;
    frm_100.set_accelerator(acc);
    EXPECT_NE(frm_100.get_accelerator(),10);
};