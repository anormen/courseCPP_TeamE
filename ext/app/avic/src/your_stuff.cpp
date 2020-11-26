//#include <chrono>
#include <thread>
#include <iostream>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include "your_stuff.h"
#include "canio/can_common.h"
#include "frames.hpp"

namespace fr=frames;

bool yourStuff::YouHaveJustRecievedACANFrame(const canfd_frame * const _frame) {

    bool isRun = true;
    std::ostringstream tempString;

    switch (_frame->can_id) {
    case 200: {
        const fr::fr200 * fr200 = reinterpret_cast<const fr::fr200*>(_frame);
        this->InstrumentCluster.setRPM(static_cast<double>(fr200->rpm));

        tempString << fr::messages.at(fr200->driverinfo);
        if(fr200->rpm > 0){
            tempString << "\n\rFuel consumption: " << std::fixed << std::setprecision(1) ;
        this->speed > 2 ? tempString << (fr200->fuelavg/100.0) << " l/100km" : tempString << (fr200->fuelinst/100.0) << " l/h"; //"2" avoid flicker at low speed
        }
        this->InstrumentCluster.setTxt(QString::fromStdString(tempString.str()));    
        this->InstrumentCluster.setTemperatureGauges(static_cast<double>(fr200->temp));

        if(fr200->updatebit && this->icon.engine_check  == false && this->isRunning){
            aliveTimeECM->start(1000);
            this->icon.engine_check = false;
            this->InstrumentCluster.setIcon(&this->icon);
        }
        break;
    }
    case 100: {
        const fr::fr100 * fr100 = reinterpret_cast<const fr::fr100*>(_frame);
        this->InstrumentCluster.setGear(QString::fromStdString(fr::gears.at(fr100->gearlever)));
        this->InstrumentCluster.setFuelGauges(static_cast<double>(fr100->accelerator * (static_cast<double>(255)/static_cast<double>(100))));        
        fr100->brake > 0 ? this->icon.hand_break = false : this->icon.hand_break = true;
        this->InstrumentCluster.setIcon(&this->icon);
        if((fr::SimulationMode)fr100->mode == fr::SimulationMode::ACTIVE && this->isStart == true){
            this->isStart = false; 
            this->InstrumentCluster.ignite(true);
            this->icon.oil_check = 1;
            this->icon.battery = 1;
            this->icon.engine_check = 1;
            this->icon.abs = 1;
            this->InstrumentCluster.setIcon(&this->icon);
            QTimer::singleShot(2000, this, [this](){  //bus read delay for start anim
                this->isRunning = true; 
                this->InstrumentCluster.setIcon(&this->icon); 
                this->icon.oil_check = 0; this->icon.battery = 0; this->icon.engine_check = 0; this->icon.abs = 0; 
            }); 
        }
        isRun = (fr::SimulationMode)fr100->mode == fr::SimulationMode::OFF ? false : true;
        break;
    }
    case 300: {
        const fr::fr300 * fr300 = reinterpret_cast<const fr::fr300*>(_frame);
        this->InstrumentCluster.setGearPindle(static_cast<char>(fr300->gearactual));
        this->InstrumentCluster.setSpeed(static_cast<double>(fr300->speed / static_cast<double>(10)));
        this->speed = fr300->speed / static_cast<double>(10);

        if(fr300->updatebit && this->icon.engine_check  == false && this->isRunning){
            aliveTimeTCM->start(1000);
            this->icon.engine_check = false;
            this->InstrumentCluster.setIcon(&this->icon);
        }            
        break;
    }    
    default:
        break;
    }
    return isRun;
}

/*
void yourStuff::startUp(unsigned char &_data) {
    //do something
}*/
















/******************************* ANYTHING BELOW THIS LINE IS JUST BORING STUFF *******************************/

yourStuff::yourStuff(const std::string &_ifName, QObject *_vs) {

    if(!(this->CANReader.open(_ifName))) exit(-1);//emit die();
    this->InstrumentCluster.init(_vs);
    this->startTimer(1);
    aliveTimeTCM = new QTimer(this);
    aliveTimeECM = new QTimer(this);   
    connect(aliveTimeECM, &QTimer::timeout, [this] (){ this->icon.engine_check = true; this->InstrumentCluster.setIcon(&this->icon); });
    connect(aliveTimeTCM, &QTimer::timeout, [this] (){ this->icon.engine_check = true; this->InstrumentCluster.setIcon(&this->icon); });    
}

bool yourStuff::run() {
    
    bool ret = true;
    canfd_frame frame; 
   
    CANOpener::ReadStatus status = this->CANReader.read(&frame);    

    if (status == CANOpener::ReadStatus::ERROR) ret = false;

    else if (status == CANOpener::ReadStatus::NAVAL ||
             status == CANOpener::ReadStatus::ENDOF) this->Counter++;

    else if (status == CANOpener::ReadStatus::OK) {
        this->Counter = 0;
        if(this->isRunning || this->isStart)
             ret = this->YouHaveJustRecievedACANFrame(&frame);
    }
    return ret;
}

void yourStuff::timerEvent(QTimerEvent*) {
    if(this->run());
    else {
//    emit this->die();
    exit(-1);
    }
}