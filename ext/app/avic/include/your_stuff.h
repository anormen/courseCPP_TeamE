#ifndef YOUR_STUFF_H
#define YOUR_STUFF_H
#include "can_opener.h"
#include "cluster_updater.h"
#include <string>
#include <QTimer>

#include <iomanip>

class yourStuff : public QObject {
    Q_OBJECT
public:
    yourStuff() = delete;
    yourStuff(const std::string &_ifName, QObject *_);



private:
    bool run();
    void YouHaveJustRecievedACANFrame(const canfd_frame * const _frame);
    void readMyEngineFrame(const unsigned char * const _data);
    void timerEvent(QTimerEvent*) override;
    uint16_t speed = 0;
    _icons icon = {0};
    QTimer* aliveTimeTCM;
    QTimer* aliveTimeECM;

//signals:
//    void die();

private:
    size_t Counter;
    CANOpener CANReader;
    ClusterUpdater InstrumentCluster;

};

#endif // YOUR_STUFF_H
