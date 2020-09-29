#include <QtTest>
#include "testexec.h"

#include "score_board/team.h"
#include "file/file_manager.h"
#include <QSignalSpy>

class UtTeam : public QObject{
    Q_OBJECT

private slots:
    void consdtruct_with_id_test(){
        Team team(testId);
        QCOMPARE(team.id, testId);
    }

    void setTeamName_test(){
        Team team(testId);
        team.setTeamName("testName");
        QCOMPARE(team.teamName.getString(), QString("testName"));
    }

    void setInvert_test(){
        Team team(testId);
        team.addRound();
        QCOMPARE(team.getRound(), QString("●○"));
        team.setInvert(true);
        QCOMPARE(team.getRound(), QString("○●"));
    }

    void addPoint_getPoint_resetPoint_test(){
        Team team(testId);
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
        Team team(testId);
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
        Team team(testId);
        QDir dir = FileManager::inst()->getScoreFileDir();
        team.registeNameFile();
        QVERIFY(dir.exists(testId + "Name.txt"));
        team.registePointFile();
        QVERIFY(dir.exists(testId + "Points.txt"));
        team.registeRoundFile();
        QVERIFY(dir.exists(testId + "RoundPoints.txt"));
    }

private:
    const QString testId = "testTeam";
};

ADD_TEST(UtTeam)
