#include "team.h"
#include "file/file_manager.h"

Team::Team(quint8 id, QObject *parent):
    QObject(parent), id(id){

}

void Team::setTeamName(QString const &name){
    teamName.setString(name);
}

void Team::setInvert(bool flag){
    rounds.setInvert(flag);
    emit(contentUpdate());
}

void Team::settingUpdate(){
    rounds.settingUpdate();
    emit(contentUpdate());
}

qint8 Team::getPoint(){
    return points.getPoint();
}

QString Team::getRound(){
    return rounds.getString();
}

QString Team::registeNameFile(){
    return FileManager::inst()->registeScoreFile(&teamName, "team" + QString::number(id) + "Name.txt");
}

QString Team::registePointFile(){
    return FileManager::inst()->registeScoreFile(&points, "team" + QString::number(id) + "Points.txt");
}

QString Team::registeRoundFile(){
    return FileManager::inst()->registeScoreFile(&rounds, "team" + QString::number(id) + "RoundPoints.txt");
}

void Team::addPoint(){
    points.addPoint(1);
    emit(contentUpdate());
}

void Team::addRound(){
    rounds.addPoint(1);
    emit(contentUpdate());
}

void Team::resetPoint(){
    points.reset();
    emit(contentUpdate());
}

void Team::resetRound(){
    rounds.reset();
    emit(contentUpdate());
}
