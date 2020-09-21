#include "datetimetimer.h"

DateTimeTimer::DateTimeTimer(QString const &format):
    format(format){

}

void DateTimeTimer::setFormat(QString const &format){
    this->format = format;
}

QString DateTimeTimer::getString(){
    return currentTime.toString(format);
}

void DateTimeTimer::timeUpdate(){
    currentTime = QDateTime::currentDateTime();
}
