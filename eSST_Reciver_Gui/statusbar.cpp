#include "statusbar.h"
#include "utility/signal_bus.h"
#include <QDebug>

StatusBar::StatusBar(QStatusBar *bar, QObject *parent):
    QObject(parent), statusBar(bar){
    connect(SignalBus::inst(), SIGNAL(systemMessageEvent(QString)), this, SLOT(systemMessageEvent(QString)));
}

void StatusBar::systemMessageEvent(QString msg){
    statusBar->showMessage(msg, 5000);
}
