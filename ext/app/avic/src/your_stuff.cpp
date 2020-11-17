//#include <chrono>
#include <thread>
#include <iostream>
#include <cstring>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include "your_stuff.h"
#include "canio/can_common.h"
#include "frames.hpp"

void yourStuff::YouHaveJustRecievedACANFrame(const canfd_frame * const _frame) {
   
    fr300 frm_300;
    fr200 frm_200;
    fr100 frm_100;
    _icons icon = {0};

    switch (_frame->can_id) {
    case 200: {
        memcpy(&frm_200,_frame,sizeof(struct fr200));
        this->InstrumentCluster.setRPM(static_cast<double>(frm_200.rpm ));
        this->InstrumentCluster.setFuelGauges(static_cast<double>(frm_200.fuelinst/10 ));
        this->InstrumentCluster.setTxt(QString::fromStdString(messages.at(frm_200.driverinfo)));
        //this->InstrumentCluster.set(QString::fromStdString(messages.at(frm_200.driverinfo)));        
        std::cout << "static_cast<double>(frm_200.temp) = " << static_cast<double>(frm_200.temp) << std::endl;
        this->InstrumentCluster.setTemperatureGauges(static_cast<double>(frm_200.temp));
        break;
    }
    case 100: {
        memcpy(&frm_100,_frame,sizeof(struct fr100));
        this->InstrumentCluster.setGear(QString::fromStdString(gears.at(frm_100.gearlever)));
        frm_100.brake > 0 ? icon.hand_break = false :icon.hand_break = true;
        this->InstrumentCluster.setIcon(&icon);
        break;
    }
    case 300: {
        memcpy(&frm_300,_frame,sizeof(struct fr300));
        this->InstrumentCluster.setGearPindle(static_cast<char>(frm_300.gearactual));
        this->InstrumentCluster.setSpeed(static_cast<double>(frm_300.speed));
        break;
    }    
    default:
        break;
    }

}

void yourStuff::readMyEngineFrame(const unsigned char * const _data) {
    this->InstrumentCluster.setSpeed(static_cast<double>(_data[0]));
}














/******************************* ANYTHING BELOW THIS LINE IS JUST BORING STUFF *******************************/

yourStuff::yourStuff(const std::string &_ifName, QObject *_vs) {
    if(!(this->CANReader.open(_ifName))) exit(-1);//emit die();
    this->InstrumentCluster.init(_vs);
    this->startTimer(1);
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
        this->YouHaveJustRecievedACANFrame(&frame);
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

