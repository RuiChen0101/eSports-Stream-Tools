#include "timetick.h"

TimeTick* TimeTick::inst(){
    static TimeTick Inst;
    return &Inst;
}

TimeTick::TimeTick(QObject *parent) : QObject(parent){
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SIGNAL(timeUpdate()));
    timer->start(1000);
}

TimeTick::~TimeTick(){
    delete timer;
}
