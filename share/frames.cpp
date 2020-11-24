#include "frames.hpp"

// Frame 100

namespace frames { 

frame_100::frame_100() { this->init_frame(); }
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
    //std::cout << "frame 100 initialized\n";
}
SimulationMode frame_100::get_mode() { return static_cast<SimulationMode>(this->frame.mode); }
GearLeverPos frame_100::get_gearlever() { return static_cast<GearLeverPos>(this->frame.gearlever); }
StartButtonSts frame_100::get_startstop() { return static_cast<StartButtonSts>(this->frame.startstop); }
uint8_t frame_100::get_updatebit() { return this->frame.updatebit; }
uint8_t frame_100::get_accelerator() { return this->frame.accelerator; }
uint8_t frame_100::get_brake() { return this->frame.brake; }
fr100 *frame_100::get_frame_ptr() { return &this->frame; }
uint8_t frame_100::get_length() { return this->frame.candlc; }
uint32_t frame_100::get_id() {return this->frame.canid;}

void frame_100::set_mode(const SimulationMode &mode) { this->frame.mode = static_cast<uint8_t>(mode); }
void frame_100::set_gearlever(const GearLeverPos &lever) { this->frame.gearlever = static_cast<uint8_t>(lever); }
void frame_100::set_startstop(const StartButtonSts &sbs) { this->frame.startstop = static_cast<uint8_t>(sbs); }
void frame_100::set_updatebit(const uint8_t &ub) { this->frame.updatebit = ub; }
void frame_100::set_accelerator(const uint8_t &acc) { this->frame.accelerator = acc; }
void frame_100::set_brake(const uint8_t &brk) { this->frame.brake = brk; }

// Frame 200

frame_200::frame_200() { this->init_frame(); }
void frame_200::init_frame()
{
    frame.rpm = 0;
    frame.fuelavg = 0;
    frame.fuelinst = 0;
    frame.driverinfo = 0;
    frame.telltale = 0;
    frame.updatebit = 0;
    frame.temp = 0;
    //std::cout << "frame 200 initialized\n";
}
uint16_t frame_200::get_rpm() { return this->frame.rpm; }
double frame_200::get_fuelinst() { return (double)(this->frame.fuelinst / 100.0); }
double frame_200::get_fuelavg() { return (double)(this->frame.fuelavg / 100.0); }
DriverInformation frame_200::get_driverinfo() { return static_cast<DriverInformation>(this->frame.driverinfo); }
Telltale frame_200::get_telltale() { return static_cast<Telltale>(this->frame.telltale); }
uint8_t frame_200::get_updatebit() { return this->frame.updatebit; }
fr200 *frame_200::get_frame_ptr() { return &this->frame; }
uint8_t frame_200::get_length() { return this->frame.candlc; }
uint8_t frame_200::get_temp() { return this->frame.temp; }
uint32_t frame_200::get_id() {return this->frame.canid;}

void frame_200::set_rpm(const uint16_t rpm) { this->frame.rpm = rpm; }
void frame_200::set_fuelinst(const double fuelinst) { this->frame.fuelinst = (uint16_t)(fuelinst * 100); }
void frame_200::set_fuelavg(const double fuelavg) { this->frame.fuelavg = (uint16_t)(fuelavg * 100) ; }
void frame_200::set_driverinfor(const DriverInformation di) { this->frame.driverinfo = static_cast<uint8_t>(di); }
void frame_200::set_telltale(const uint8_t tt) { this->frame.telltale = tt; }
void frame_200::set_updatebit(const uint8_t &ub) { this->frame.updatebit = ub; }
void frame_200::set_temp(const uint8_t &tmp) { this->frame.temp = tmp; }

// Frame 300

frame_300::frame_300() { this->init_frame(); }
void frame_300::init_frame()
{
    frame.speed = 0;
    frame.gearactual = 1;
    frame.gearRatio = 10;
    frame.res1 = 0;
    frame.res2 = 0;
    frame.res3 = 0;
    frame.res4 = 0;
    frame.updatebit = 0;
    //std::cout << "frame 300 initialized\n";
}
uint16_t frame_300::get_speed(){return (this->frame.speed / 10.0);}
uint8_t frame_300::get_gearactual(){return this->frame.gearactual;}

uint8_t frame_300::get_updatebit(){return this->frame.updatebit;}
fr300 *frame_300::get_frame_ptr(){return &this->frame;}
uint8_t frame_300::get_length(){return this->frame.candlc;}
uint8_t frame_300::get_gearratio(){return this->frame.gearRatio;}
uint32_t frame_300::get_id() {return this->frame.canid;}

void frame_300::set_speed(const uint16_t spd){this->frame.speed= spd * 10;}
void frame_300::set_gearactual(const uint8_t gearact){this->frame.gearactual=gearact;}
void frame_300::set_updatebit(const uint8_t &ub){this->frame.updatebit=ub;}
void frame_300::set_gearratio(const uint8_t &gr){this->frame.gearRatio=gr;}

} // namespace frames