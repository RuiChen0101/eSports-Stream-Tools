#include "signal_bus.h"

SignalBus* SignalBus::inst(){
    static SignalBus Inst;
    return &Inst;
}

SignalBus::SignalBus(QObject *parent):
    QObject(parent){
}
