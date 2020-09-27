#include "chrono_down_timer.h"

ChronoDownTimer::ChronoDownTimer(){
    parser.setDoubleDigit(true);
}

void ChronoDownTimer::timeUpdate(){
    if(status == START || status == RESUME){
        remainSec -= remainSec >= 0 ? 1 : 0;
        parser.setSecond(remainSec);
        emit(contentUpdate());
    }
}

QString ChronoDownTimer::getString(){
    if(status != STOP){
        if(remainSec < 0){
            return timeoutMsg;
        }else{
            return parser.getString();
        }
    }else{
        return "";
    }
}

bool ChronoDownTimer::isOutputing() const{
    return status != STOP;
}

void ChronoDownTimer::setFormat(QString const &format){
    parser.setFormat(format);
}

void ChronoDownTimer::setTarget(QTime const &target){
    this->target = target;
}

void ChronoDownTimer::setStatus(Status stat){
    this->status = stat;
    if(this->status == START){
        remainSec = QTime(0, 0, 0).secsTo(target);
        parser.setSecond(remainSec);
    }
    emit(contentUpdate());
}

void ChronoDownTimer::setTimeoutMsg(QString const &msg){
    this->timeoutMsg = msg;
}

void ChronoDownTimer::setDoubleDigit(bool flag){
    parser.setDoubleDigit(flag);
}
