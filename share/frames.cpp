#include <iostream>
#include "frames.hpp"

// Frame 100

frame_100::frame_100() { this->init_frame(); };
void frame_100::init_frame()
{
    this->frame.mode = 0;
    this->frame.gearlever = 0;
    this->frame.startstop = 0;
    this->frame.updatebit = 0;
    this->frame.accelerator = 0;
    this->frame.brake = 0;
    this->frame.res0 = 0;
    this->frame.res1 = 0;
    this->frame.res2 = 0;
    this->frame.res3 = 0;
    this->frame.res4 = 0;
    std::cout << "frame 100 initialized\n";
}
SimulationMode frame_100::get_mode() { return static_cast<SimulationMode>(this->frame.mode); }
GearLeverPos frame_100::get_gearlever() { return static_cast<GearLeverPos>(this->frame.gearlever); }
StartButtonSts frame_100::get_startstop() { return static_cast<StartButtonSts>(this->frame.startstop); }
uint8_t frame_100::get_updatebit() { return this->frame.updatebit; }
uint8_t frame_100::get_accelerator() { return this->frame.accelerator; }
uint8_t frame_100::get_brake() { return this->frame.brake;}
fr100* frame_100::get_frame_ptr(){return &this->frame;};
uint8_t frame_100::get_length(){return this->frame.candlc;};

void frame_100::set_mode(SimulationMode &mode) { this->frame.mode = static_cast<uint8_t>(mode); }
void frame_100::set_gearlever(GearLeverPos &lever) { this->frame.gearlever = static_cast<uint8_t>(lever); }
void frame_100::set_startstop(StartButtonSts &sbs) { this->frame.gearlever = static_cast<uint8_t>(sbs); }
void frame_100::set_updatebit(uint8_t &ub) { this->frame.updatebit = ub; }
void frame_100::set_accelerator(uint8_t &acc) { this->frame.accelerator = acc; }
void frame_100::set_brake(uint8_t &brk) { this->frame.brake = brk; }

// Frame 200

frame_200::frame_200() { this->init_frame(); };
void frame_200::init_frame()
{
    frame.rpm = 0;
    frame.fuel = 0;
    frame.driverinfo = 0;
    frame.telltale = 0;
    frame.updatebit = 0;
    frame.res0 = 0;
    frame.res1 = 0;
    frame.res2 = 0;
    std::cout << "frame 200 initialized\n";
}
uint16_t frame_200::get_rpm() { return this->frame.rpm; }
uint16_t frame_200::get_fuel() { return this->frame.fuel; }
DriverInformation frame_200::get_driverinfo() { return static_cast<DriverInformation>(this->frame.driverinfo); }
uint8_t frame_200::get_telltale() { return this->frame.telltale; }
uint8_t frame_200::get_updatebit() { return this->frame.updatebit; }
fr200* frame_200::get_frame_ptr(){return &this->frame;};
uint8_t frame_200::get_length(){return this->frame.candlc;};

void frame_200::set_rpm(uint16_t rpm) { this->frame.rpm = rpm; }
void frame_200::set_fuel(uint16_t fuel) { this->frame.fuel = fuel; }
void frame_200::set_driverinfor(DriverInformation di) { this->frame.driverinfo = static_cast<uint8_t>(di); }
void frame_200::set_telltale(uint8_t tt) { this->frame.telltale = tt; }
void frame_200::set_updatebit(uint8_t ub) { this->frame.updatebit = ub; }
