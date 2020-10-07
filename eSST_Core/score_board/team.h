#ifndef TEAM_H
#define TEAM_H

#include "point.h"
#include "round.h"
#include "file/file_source.h"

#include <QObject>
#include <QString>

class Team : public QObject{
    Q_OBJECT
friend class UtTeam;

public:
    Team(quint8, QObject *parent = nullptr);
    quint8 getId();
    qint8 getPoint();
    QString getRound();
    QString registeNameFile();
    QString registePointFile();
    QString registeRoundFile();
    void setTeamName(QString const &);
    void setInvert(bool);
    void settingUpdate();

public slots:
    void addPoint();
    void addRound();
    void resetPoint();
    void resetRound();

signals:
    void contentUpdate();

private:
    quint8 id;
    Point points;
    Round rounds;
    FileSource teamName;
};

#endif // TEAM_H
