#include "point.h"

Point::Point():
    points(0){

}

void Point::reset(){
    points = 0;
    emit(contentUpdate());
}

void Point::addPoint(qint8 add){
    points += add;
    emit(contentUpdate());
}

qint8 Point::getPoint() const{
    return points;
}

QString Point::getString(){
    return QString::number(points);
}

bool Point::isOutputing() const {
    return true;
}
