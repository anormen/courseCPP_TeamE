//#include <chrono>
#include <thread>
#include <iostream>
#include <cstring>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include "your_stuff.h"
#include "canio/can_common.h"
#include "frames.hpp"

namespace CANID {
const canid_t ENGINE_AND_GEARBOX = 0x123;
const canid_t ICONZ = 0x213;
}



void yourStuff::YouHaveJustRecievedACANFrame(const canfd_frame * const _frame) {
    fr200 frm_200;
    fr100 frm_100;

    switch (_frame->can_id) {
    case CAN::MSG::GAUGES_ID: {
        const struct CAN::MSG::Gauges_t::_inner* s = reinterpret_cast<const struct CAN::MSG::Gauges_t::_inner* >((_frame->data));

        this->InstrumentCluster.setFuelGauges(s->G_FUEL);
        this->InstrumentCluster.setTemperatureGauges(s->G_TEMP);
        this->InstrumentCluster.setOilTemperatureGauges(s->G_OILT);
        CAN::MSG::printGauges(s);
    }
        break;
    case 200: {
        memcpy(&frm_200,_frame,sizeof(struct fr200));
        this->InstrumentCluster.setRPM(static_cast<double>(frm_200.rpm ));
        this->InstrumentCluster.setFuelGauges(static_cast<double>(frm_200.fuelinst/10 ));
        this->InstrumentCluster.setTxt(QString::fromStdString(messages.at(frm_200.driverinfo)));
        break;
    }
    case 100: {
        memcpy(&frm_100,_frame,sizeof(struct fr100));
        this->InstrumentCluster.setGearPindle(static_cast<char>(frm_100.gearlever));
        this->InstrumentCluster.setGear(static_cast<char>(frm_100.gearlever));

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

