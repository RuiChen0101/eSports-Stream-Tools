#include "date_time_timer.h"

DateTimeTimer::DateTimeTimer(QString const &format):
    format(format){}

bool DateTimeTimer::isOutputing() const{
    return true;
}

void DateTimeTimer::setFormat(QString const &format){
    this->format = format;
}

QString DateTimeTimer::getString(){
    return currentTime.toString(format);
}

void DateTimeTimer::timeUpdate(){
    currentTime = QDateTime::currentDateTime();
    emit(contentUpdate());
}
