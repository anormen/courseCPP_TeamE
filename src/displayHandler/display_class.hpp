#ifndef _DISPLAY_CLASS_H_
#define _DISPLAY_CLASS_H_ 
#include "frames.hpp"

namespace fr=frames;

class display{

    public:
        display(){};
        void initDisplay();
        void update();
        void setValueAcc(int _acc){ accelerator = _acc; };
        void setValueRpm(int _rpm){ rpm = _rpm; };
        void setValueBrake(int _brake){ brake = _brake; };        
        void setValueMode(fr::SimulationMode _mode){  mode = _mode; }; 
        fr::SimulationMode getValueMode(){ return mode; };         
        void setValueStartStop(fr::StartButtonSts _start){  startstop = _start; };      
        void setValueGearLever(fr::GearLeverPos _gearlever){ gearlever = _gearlever; };
        void setValueDriverInfo(fr::DriverInformation _driverinfo){  driverinfo = _driverinfo; };
        void setValueGearActual(int _gearactual){  gearactual = _gearactual; };        
        void setValueVehicleSpeed(float _vehiclespeed){  vehiclespeed = _vehiclespeed; }; 
        void setValueFuelConsumptionAvg(double _fuelconsumavg){  fuelconsumavg = _fuelconsumavg; }; 
        void setValueFuelConsumptionInst(double _fuelconsuminst){  fuelconsuminst = _fuelconsuminst; };         
        void setValueTelltale(fr::Telltale _telltale){  telltale = _telltale; };   
        void setValueGearRatio(int _gearratio){  gearratio = _gearratio; };                
        void setValueInputUB(bool _inputUb){ inputUb = _inputUb; };
        void setValueECMUB(bool _ecmUb){  ecmUb = _ecmUb; };
        void setValueTCMUB(bool _tcmUb){  tcmUb = _tcmUb; };                               
        ~display(){};
    private:
        int accelerator = 0;
        int rpm = 0;
        int brake = 0;
        void updateTelltale();  
        uint16_t updateTimeout = 0;  
        fr::SimulationMode mode = fr::SimulationMode::SLEEP;
        fr::StartButtonSts startstop = fr::StartButtonSts::UNPRESSED;         
        fr::GearLeverPos gearlever = fr::GearLeverPos::PARK; 
        fr::DriverInformation driverinfo = fr::DriverInformation::NO_MSG;
        int gearactual = 0; 
        int gearratio = 0;    
        float vehiclespeed = 0;
        double fuelconsumavg = 0; 
        double fuelconsuminst = 0;         
        fr::Telltale telltale = fr::Telltale::PRESENT;
        bool inputUb = 0;     
        bool ecmUb = 0;
        bool tcmUb = 0;         
};

#endif