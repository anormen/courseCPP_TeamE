#ifndef _DISPLAY_CLASS_H_
#define _DISPLAY_CLASS_H_ 
#include "frames.hpp"

class display{

    public:
        display(){};
        void initDisplay();
        void update();
        void setValueAcc(int _acc){ accelerator = _acc; };
        void setValueRpm(int _rpm){  rpm = _rpm; };
        void setValueBrake(int _brake){  brake = _brake; };        
        void setValueMode(SimulationMode _mode){  mode = _mode; }; 
        SimulationMode getValueMode(){  return mode; };         
        void setValueStartStop(StartButtonSts _start){  startstop = _start; };      
        void setValueGearLever(GearLeverPos _gearlever){ gearlever = _gearlever; };
        void setValueDriverInfo(DriverInformation _driverinfo){  driverinfo = _driverinfo; };
        void setValueGearActual(int _gearactual){  gearactual = _gearactual; };        
        void setValueVehicleSpeed(float _vehiclespeed){  vehiclespeed = _vehiclespeed; }; 
        void setValueFuelConsumptionAvg(float _fuelconsumavg){  fuelconsumavg = _fuelconsumavg; }; 
        void setValueFuelConsumptionInst(float _fuelconsuminst){  fuelconsuminst = _fuelconsuminst; };         
        void setValueTelltale(float _telltale){  telltale = _telltale; };         
        void setValueInputUB(bool _inputUb){ inputUb = _inputUb; };
        void setValueECMUB(bool _ecmUb){  ecmUb = _ecmUb; };
        void setValueTCMUB(bool _tcmUb){  tcmUb = _tcmUb; };                               
        ~display(){};
    private:
        int accelerator = 0;
        int rpm = 0;
        int brake = 0;
        void updateTelltale();    
        SimulationMode mode = SimulationMode::SLEEP;
        StartButtonSts startstop = StartButtonSts::UNPRESSED;         
        GearLeverPos gearlever = GearLeverPos::PARK; 
        DriverInformation driverinfo = DriverInformation::NO_MSG;
        int gearactual = 0;     
        float vehiclespeed = 0;
        double fuelconsumavg = 0; 
        double fuelconsuminst = 0;         
        uint8_t telltale = 0;
        bool inputUb = 0;     
        bool ecmUb = 0;
        bool tcmUb = 0;         
};

#endif