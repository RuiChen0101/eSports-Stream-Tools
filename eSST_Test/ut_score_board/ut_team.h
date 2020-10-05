#include <QtTest>
#include "testexec.h"

#include "score_board/team.h"
#include "file/file_manager.h"
#include <QSignalSpy>

class UtTeam : public QObject{
    Q_OBJECT

private slots:
    void consdtruct_with_id_test(){
        Team team(0);
        QCOMPARE(team.id, 0);
    }

    void setTeamName_test(){
        Team team(0);
        team.setTeamName("testName");
        QCOMPARE(team.teamName.getString(), QString("testName"));
    }

    void setInvert_test(){
        Team team(0);
        team.addRound();
        QCOMPARE(team.getRound(), QString("●○"));
        team.setInvert(true);
        QCOMPARE(team.getRound(), QString("○●"));
    }

    void addPoint_getPoint_resetPoint_test(){
        Team team(0);
        QCOMPARE(team.getPoint(), qint8(0));
        QSignalSpy spy(&team, SIGNAL(contentUpdate()));
        team.addPoint();
        QCOMPARE(team.getPoint(), qint8(1));
        QCOMPARE(spy.count(), 1);
        spy.clear();
        team.resetPoint();
        QCOMPARE(team.getPoint(), qint8(0));
        QCOMPARE(spy.count(), 1);
        spy.clear();
    }

    void addRound_getRound_resetPoint_test(){
        Team team(0);
        QCOMPARE(team.getRound(), QString("○○"));
        QSignalSpy spy(&team, SIGNAL(contentUpdate()));
        team.addRound();
        QCOMPARE(team.getRound(), QString("●○"));
        QCOMPARE(spy.count(), 1);
        spy.clear();
        team.resetRound();
        QCOMPARE(team.getRound(), QString("○○"));
        QCOMPARE(spy.count(), 1);
        spy.clear();
    }

    void registe_file_test(){
        Team team(0);
        QDir dir = FileManager::inst()->getScoreFileDir();
        team.registeNameFile();
        QVERIFY(dir.exists("team0Name.txt"));
        team.registePointFile();
        QVERIFY(dir.exists("team0Points.txt"));
        team.registeRoundFile();
        QVERIFY(dir.exists("team0RoundPoints.txt"));
    }
};

ADD_TEST(UtTeam)
