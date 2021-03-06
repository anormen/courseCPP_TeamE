#ifndef CLUSTERUPDATE_H
#define CLUSTERUPDATE_H
#include <QtCore/QObject>
#include <QtCore/QVariant>

struct _icons {
    unsigned short hazard : 1;
    unsigned short right_blinker : 1;
    unsigned short left_blinker : 1;
    unsigned short engine_check : 1;
    unsigned short oil_check : 1;
    unsigned short abs : 1;
    unsigned short battery : 1;
    unsigned short seat_belt : 1;
    unsigned short doors_open : 1;
    unsigned short high_beam : 1;
    unsigned short hand_break : 1;
    unsigned short _reserved_pad : 5;
}__attribute__((packed));

class ClusterUpdater/* : public QObject*/ {
//    Q_OBJECT
public:
    ClusterUpdater() = default;
    inline void init(QObject*_){this->ValueSource=_;}
    
    QObject *ValueSource;

public:
    void setIcon(const _icons *_i);

    inline void setGear(const QString &_s) {ValueSource->setProperty("prindle",QVariant(_s));}
    inline void setRPM(const double &_s) {ValueSource->setProperty("rpmHezar",QVariant(_s));}
    inline void setSpeed(const double &_s) {ValueSource->setProperty("kph",QVariant(_s));}
    inline void setGearPindle(const char &_p) {ValueSource->setProperty("gear",QVariant(_p));}
    inline void setFuelGauges(const double &_f) {ValueSource->setProperty("fuel",QVariant(_f/0xFF));}
    inline void setTemperatureGauges(const double &_t) {ValueSource->setProperty("temperature",QVariant(_t/0xFF));}
    inline void setOilTemperatureGauges(const double&_t) {ValueSource->setProperty("oil_temp",QVariant(_t/0xFF));}
    inline void setTxt(const QString &_s) {ValueSource->setProperty("txt",QVariant(_s));}
    /** 0: off 1: on **/
    inline void ignite(const int &_t) {ValueSource->setProperty("startUp",QVariant(_t));}    

private:
    unsigned short iconZ;
};

#endif // CLUSTERUPDATE_H