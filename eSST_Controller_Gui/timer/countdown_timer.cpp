#include "countdown_timer.h"

CountDownTimer::CountDownTimer(){
    parser.setDoubleDigit(true);
}

void CountDownTimer::timeUpdate(){
    if(status == START){
        remainSec -= remainSec >= 0 ? 1 : 0;
        parser.setSecond(remainSec);
        emit(contentUpdate());
    }
}

QString CountDownTimer::getString(){
    if(status == START){
        if(remainSec < 0){
            return timeoutMsg;
        }else{
            return parser.getString();
        }
    }else{
        return "";
    }
}

bool CountDownTimer::isOutputing() const{
    return status != STOP;
}

void CountDownTimer::setFormat(QString const &format){
    parser.setFormat(format);
}

void CountDownTimer::setTarget(QDateTime const &target){
    QDateTime currentTime = QDateTime::currentDateTime();
    remainSec = currentTime.secsTo(target);
    parser.setSecond(remainSec);
}

void CountDownTimer::setStatus(Status stat){
    this->status = stat;
    if(status == START){
        parser.setSecond(remainSec);
    }
    emit(contentUpdate());
}

void CountDownTimer::setTimeoutMsg(QString const &msg){
    this->timeoutMsg = msg;
}

void CountDownTimer::setDoubleDigit(bool flag){
    parser.setDoubleDigit(flag);
}
