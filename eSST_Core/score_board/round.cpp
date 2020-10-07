#include "round.h"
#include <QDebug>

qint8 Round::bestOf = 3;
QString Round::format = "○●";
bool Round::useDigit = false;

Round::Round():
    points(0), isInvert(false){

}

void Round::setUseDigit(bool flag){
    Round::useDigit = flag;
}

void Round::setFormat(QString const &format){
    Round::format = format;
}

void Round::setBestOf(qint8 bestOf){
    Round::bestOf = bestOf;
}

void Round::addPoint(qint8 add){
    points += (points+add) <= (Round::bestOf+1)/2 ? add : 0;
    emit(contentUpdate());
}

QString Round::getString(){
    if(Round::useDigit){
        return QString::number(points);
    }else{
        if(Round::format.size() == 2){
            return parseFormat();
        }else{
            return "format error";
        }
    }
}

QString Round::parseFormat(){
    QString result = "";
    for(int i=0 ; i<(Round::bestOf+1)/2 ; i++){
        if(i >= points){
            result += Round::format[0];
        }else{
            result += Round::format[1];
        }
    }
    if(isInvert){
        std::reverse(result.begin(), result.end());
    }
    return result;
}

bool Round::isOutputing() const{
    return true;
}

void Round::setInvert(bool flag){
    this->isInvert = flag;
    emit(contentUpdate());
}

void Round::settingUpdate(){
    emit(contentUpdate());
}

void Round::reset(){
    points = 0;
    emit(contentUpdate());
}
