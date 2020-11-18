#ifndef _FRAMES_H
#define _FRAMES_H
#include <cstdint>
#include <vector>
#include <string>
#include <mutex>

enum class GearLeverPos : uint8_t {PARK, REVERSE, NEUTRAL, DRIVE};
enum class StartButtonSts : uint8_t {UNPRESSED, PRESSED};
enum class SimulationMode : uint8_t { SLEEP, INACTIVE, ACTIVE, OFF};
enum class DriverInformation : uint8_t { NO_MSG, NO_BRAKE, NOT_IN_P, NOT_IN_P_IN_D, NO_KEY};
enum class Telltale : uint8_t { PRESENT, ECM, TCM, INPUT};

static std::vector<std::string> messages = {"No message", "No Brake pressed", "Gear not in P" , "Gear not in P, select P to turn off", "No key found", "", "", "", "", "", "", "" , "", "", "", ""};
static std::vector<std::string> gears = {"P", "R", "N" , "D" , "1", "2", "3", "4", "5", "6", "7", "8", "9", "", "", "" };
static std::vector<std::string> modes = { "SLEEP", "INACTIVE", "ACTIVE", "OFF" };
static std::vector<std::string> telltales = { "OK", "MISSING ECM", "MISSING TCM", "MISSING INPUT" };

//frame cycle times
const uint16_t fr100_updateRate = 50;
const uint16_t fr200_updateRate = 50;
const uint16_t fr300_updateRate = 50;

//frame from inputhandler
struct fr100{
//header
    uint32_t canid = 100;; 
    uint8_t candlc = 8;
    uint8_t canpad = 0;
    uint8_t canres0 = 0;
    uint8_t canres1 = 0;
//data
    uint8_t accelerator:8;
    uint8_t brake:8;
    uint8_t startstop:1;
    uint8_t mode:2;
    uint8_t gearlever:4;
    uint8_t updatebit:1;
    uint8_t res0:8;
    uint8_t res1:8;
    uint8_t res2:8;
    uint8_t res3:8;  
    uint8_t res4:8;     
};
//frame from ECM
struct fr200{
//header
    uint32_t canid = 200;; 
    uint8_t candlc = 8;
    uint8_t canpad = 0;
    uint8_t canres0 = 0;
    uint8_t canres1 = 0;
//data
    uint16_t rpm:16;
    uint16_t fuelinst:16; //*100
    uint16_t fuelavg:16; //*100
    uint8_t driverinfo:4;
    uint8_t telltale:3;
    uint8_t updatebit:1;
    uint8_t temp:8;   
};
//frame from TCM
struct fr300{
//header
    uint32_t canid = 300;
    uint8_t candlc = 8;
    uint8_t canpad = 0;
    uint8_t canres0 = 0;
    uint8_t canres1 = 0;
//data
    uint16_t speed:16; //*10
    uint8_t gearactual:7;
    uint8_t updatebit:1;
    uint8_t gearRatio:8;
    uint8_t res1:8;
    uint8_t res2:8;
    uint8_t res3:8;  
    uint8_t res4:8;     
};

class frame_100
{
  public:
    frame_100();
    void init_frame();
    SimulationMode get_mode();
    GearLeverPos get_gearlever();
    StartButtonSts get_startstop();
    uint8_t get_updatebit();
    uint8_t get_accelerator();
    uint8_t get_brake();
    fr100* get_frame_ptr();
    uint8_t get_length();

    void set_mode(const SimulationMode &mode);
    void set_gearlever(const GearLeverPos &lever);
    void set_startstop(const StartButtonSts &sbs);
    void set_updatebit(const uint8_t &ub);
    void set_accelerator(const uint8_t &acc);
    void set_brake(const uint8_t &brk);
    std::mutex fr100_mutex;
  private:
    fr100 frame;
};


class frame_200
{
  public:
    frame_200();
    void init_frame();
    uint16_t get_rpm();
    double get_fuelinst();
    double get_fuelavg();
    DriverInformation get_driverinfo();
    Telltale get_telltale();
    uint8_t get_updatebit();
    fr200* get_frame_ptr();
    uint8_t get_length();
    uint8_t get_temp();

    void set_rpm(const uint16_t rpm);
    void set_fuelinst(double fuelinst);
    void set_fuelavg(double fuelavg);
    void set_driverinfor(const DriverInformation di);
    void set_telltale(const uint8_t tt);
    void set_updatebit(const uint8_t &ub);
    void set_temp(const uint8_t &ub);
    std::mutex fr200_mutex;
  private:
    fr200 frame;
};

class frame_300
{
  public:
    frame_300();
    void init_frame();
    uint16_t get_speed();
    uint8_t get_gearactual();
    uint8_t get_gearratio();

    uint8_t get_updatebit();
    fr300* get_frame_ptr();
    uint8_t get_length();

    void set_speed(const uint16_t spd);
    void set_gearactual(const uint8_t gearact);
    void set_updatebit(const uint8_t &ub);
    void set_gearratio(const uint8_t &gr);
    std::mutex fr300_mutex;
  private:
    fr300 frame;
};



#endif //_FRAMES_H