#include <QtTest>
#include "testexec.h"

#include "score_board/round.h"

class UtRound : public QObject{
    Q_OBJECT

private slots:
    void isOutputing_test(){
        Round round;
        QVERIFY(round.isOutputing());
    }

    void static_setter_test(){
        Round round;
        Round::setBestOf(5);
        Round::setUseDigit(true);
        Round::setFormat("AB");
        QCOMPARE(Round::bestOf, 5);
        QCOMPARE(Round::useDigit, true);
        QCOMPARE(Round::format, "AB");
    }

    void addPoint_test(){
        Round round;
        QSignalSpy spy(&round, SIGNAL(contentUpdate()));
        round.addPoint(1);
        QCOMPARE(spy.count(), 1);
        QCOMPARE(round.points, 1);
    }

    void addPoint_over_bestOf_test(){
        Round round;
        round.addPoint(1);
        QCOMPARE(round.points, 1);
        round.addPoint(2);
        QCOMPARE(round.points, 1);
    }

    void parseFormat_test(){
        Round round;
        round.addPoint(1);
        QCOMPARE(round.parseFormat(), "●○");
    }

    void parseFormat_invert_test(){
        Round round;
        round.setInvert(true);
        round.addPoint(1);
        QCOMPARE(round.parseFormat(), "○●");
    }

    void getString_use_format_test(){
        Round round;
        round.addPoint(1);
        QCOMPARE(round.getString(), "●○");
        round.addPoint(1);
        QCOMPARE(round.getString(), "●●");
    }

    void getString_change_format_test(){
        Round round;
        Round::setFormat("AB");
        round.addPoint(1);
        QCOMPARE(round.getString(), "BA");
        round.addPoint(1);
        QCOMPARE(round.getString(), "BB");
    }

    void getString_format_invert_test(){
        Round round;
        round.setInvert(true);
        round.addPoint(1);
        QCOMPARE(round.getString(), "○●");
        round.addPoint(1);
        QCOMPARE(round.getString(), "●●");
    }

    void getString_format_error_test(){
        Round round;
        Round::setFormat("123");
        QCOMPARE(round.getString(), "format error");
        Round::setFormat("1");
        QCOMPARE(round.getString(), "format error");
    }

    void getString_use_digit_test(){
        Round round;
        Round::setUseDigit(true);
        round.addPoint(1);
        QCOMPARE(round.getString(), "1");
        round.addPoint(1);
        QCOMPARE(round.getString(), "2");
    }

    void settingUpdate_test(){
        Round round;
        QSignalSpy spy(&round, SIGNAL(contentUpdate()));
        round.settingUpdate();
        QCOMPARE(spy.count(), 1);
    }

    void reset_test(){
        Round round;
        round.addPoint(1);
        QCOMPARE(round.points, 1);
        QSignalSpy spy(&round, SIGNAL(contentUpdate()));
        round.reset();
        QCOMPARE(spy.count(), 1);
        QCOMPARE(round.points, 0);
    }

    void cleanup(){
        Round::setBestOf(3);
        Round::setUseDigit(false);
        Round::setFormat("○●");
    }
};

ADD_TEST(UtRound)
