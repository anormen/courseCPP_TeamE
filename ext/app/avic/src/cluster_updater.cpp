#include "cluster_updater.h"

void ClusterUpdater::setIcon(const  _icons * icons) {

    ValueSource->setProperty("abs", QVariant( static_cast<unsigned>(icons->abs)));
    ValueSource->setProperty("hazard", QVariant( static_cast<unsigned>(icons->hazard)));
    ValueSource->setProperty("battery", QVariant( static_cast<unsigned>(icons->battery)));
    ValueSource->setProperty("high_beam", QVariant( static_cast<unsigned>(icons->high_beam)));
    ValueSource->setProperty("oil_check", QVariant( static_cast<unsigned>(icons->oil_check)));
    ValueSource->setProperty("seat_belt", QVariant( static_cast<unsigned>(icons->seat_belt)));
    ValueSource->setProperty("hand_break", QVariant( static_cast<unsigned>(icons->hand_break)));
    ValueSource->setProperty("doors_open", QVariant( static_cast<unsigned>(icons->doors_open)));
    ValueSource->setProperty("engine_check", QVariant( static_cast<unsigned>(icons->engine_check)));
    ValueSource->setProperty("left_blinker", QVariant( static_cast<unsigned>(icons->left_blinker)));
    ValueSource->setProperty("right_blinker",  QVariant( static_cast<unsigned>(icons->right_blinker)));
}

void CANOpener() {

}
