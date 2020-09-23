#include "timer_format_parser.h"

void StTimeUnit::fromSecond(qint64 time){
    this->sec = time % 60;
    time /= 60;
    this->min = time % 60;
    time /= 60;
    this->hour = time % 24;
    this->day = time / 24;
}

TimerFormatParser::TimerFormatParser():
    useDoubleDigit(false){}

void TimerFormatParser::setFormat(QString const &format){
    this->format = format;
}

void TimerFormatParser::setSecond(qint64 const &second){
    this->timeUnit.fromSecond(second);
}

void TimerFormatParser::setDoubleDigit(bool flag){
    this->useDoubleDigit = flag;
}

QString TimerFormatParser::numberToString(quint8 number){
    if(useDoubleDigit){
        return QString::number(number).rightJustified(2, '0');
    }else{
        return QString::number(number);
    }
}

QString TimerFormatParser::getString(){
    QString result = "";
    QString::const_iterator it = format.begin();
    while(it != format.end()){
        if(*it == "$"){
            if(*(it+1) == "s"){
                result += numberToString(timeUnit.sec);
                it++;
            }else if(*(it+1) == "m"){
                result += numberToString(timeUnit.min);
                it++;
            }else if(*(it+1) == "h"){
                result += numberToString(timeUnit.hour);
                it++;
            }else if(*(it+1) == "d"){
                result += numberToString(timeUnit.day);
                it++;
            }else{
                result += *it;
            }
        }else{
            result += *it;
        }
        it++;
    }
    return result;
}
