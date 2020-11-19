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
   
    fr::fr300 frm_300 = {0};
    fr::fr200 frm_200 = {0};
    fr::fr100 frm_100 = {0};
    bool isRun = true;

    std::ostringstream tempString;

    switch (_frame->can_id) {
    case 200: {
        memcpy(&frm_200,_frame,sizeof(struct fr::fr200));
        this->InstrumentCluster.setRPM(static_cast<double>(frm_200.rpm ));

        tempString << fr::messages.at(frm_200.driverinfo);
        if(frm_200.rpm > 0){
            tempString << "\n\rFuel consumption: " << std::fixed << std::setprecision(1) ;
        this->speed > 0 ? tempString << (frm_200.fuelavg/100.0) << " l/100km" : tempString << (frm_200.fuelinst/100.0) << " l/h";
        }

        this->InstrumentCluster.setTxt(QString::fromStdString(tempString.str()));    
        this->InstrumentCluster.setTemperatureGauges(static_cast<double>(frm_200.temp));

        if(frm_200.updatebit){
            aliveTimeECM->start(1000);
            this->icon.engine_check = false;
            this->InstrumentCluster.setIcon(&this->icon);
        }
        break;
    }
    case 100: {
        memcpy(&frm_100,_frame,sizeof(struct fr::fr100));
        this->InstrumentCluster.setGear(QString::fromStdString(fr::gears.at(frm_100.gearlever)));
        this->InstrumentCluster.setFuelGauges(static_cast<double>(frm_100.accelerator));        
        frm_100.brake > 0 ? this->icon.hand_break = false : this->icon.hand_break = true;
        this->InstrumentCluster.setIcon(&this->icon);
        if((fr::SimulationMode)frm_100.mode == fr::SimulationMode::ACTIVE && this->isStart == true){
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

        ((fr::SimulationMode)frm_100.mode == fr::SimulationMode::OFF) ? isRun = false : isRun = true;

       break;
    }
    case 300: {
        memcpy(&frm_300,_frame,sizeof(struct fr::fr300));
        this->InstrumentCluster.setGearPindle(static_cast<char>(frm_300.gearactual));
        this->InstrumentCluster.setSpeed(static_cast<double>(frm_300.speed));
        this->speed = frm_300.speed;

        if(frm_300.updatebit){
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

void yourStuff::startUp(unsigned char &_data) {
    //this->InstrumentCluster.ignite(false);
}
















/******************************* ANYTHING BELOW THIS LINE IS JUST BORING STUFF *******************************/

yourStuff::yourStuff(const std::string &_ifName, QObject *_vs) {

    if(!(this->CANReader.open(_ifName))) exit(-1);//emit die();
    this->InstrumentCluster.init(_vs);
    this->startTimer(1);
    aliveTimeTCM = new QTimer(this);
    aliveTimeECM = new QTimer(this);   
    connect(aliveTimeECM, &QTimer::timeout, [this] (){ this->icon.engine_check = true; this->InstrumentCluster.setIcon(&this->icon);});
    connect(aliveTimeTCM, &QTimer::timeout, [this] (){ this->icon.engine_check = true; this->InstrumentCluster.setIcon(&this->icon);});    
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
    //if (this->Counter > 200) ret = false;
    return ret;
}

void yourStuff::timerEvent(QTimerEvent*) {
    if(this->run());
    else {
//    emit this->die();
    exit(-1);
    }
}

