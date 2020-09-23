#include <QtTest>
#include "testexec.h"

#include "timer/chrono_down_timer.h"

class UtChronoDownTimer : public QObject{
    Q_OBJECT

private slots:
    void setTarget_test(){
        ChronoDownTimer timer;
        timer.setTarget(QTime(0, 1, 1));
        QCOMPARE(timer.target, QTime(0, 1, 1));
    }

    void setFormat_test(){
        ChronoDownTimer timer;
        timer.setFormat("TEST");
        QCOMPARE(timer.parser.getString(), "TEST");
    }

    void isOutputing_test(){
        ChronoDownTimer timer;
        QVERIFY(!timer.isOutputing());
        timer.setStatus(ChronoDownTimer::START);
        QVERIFY(timer.isOutputing());
        timer.setStatus(ChronoDownTimer::RESUME);
        QVERIFY(timer.isOutputing());
        timer.setStatus(ChronoDownTimer::PAUSE);
        QVERIFY(timer.isOutputing());
    }

    void start_chrono_and_update_time_test(){
        ChronoDownTimer timer;
        timer.setFormat("TEST $h:$m:$s");
        timer.setTarget(QTime(0, 1, 2));
        timer.setStatus(ChronoDownTimer::START);
        QCOMPARE(timer.getString(), "TEST 00:01:02");
        timer.timeUpdate();
        QCOMPARE(timer.getString(), "TEST 00:01:01");
        timer.timeUpdate();
        QCOMPARE(timer.getString(), "TEST 00:01:00");
        timer.timeUpdate();
        QCOMPARE(timer.getString(), "TEST 00:00:59");
    }

    void pause_chrono_and_update_time_test(){
        ChronoDownTimer timer;
        timer.setFormat("TEST $h:$m:$s");
        timer.setTarget(QTime(0, 1, 2));
        timer.setStatus(ChronoDownTimer::START);
        QCOMPARE(timer.getString(), "TEST 00:01:02");
        timer.timeUpdate();
        QCOMPARE(timer.getString(), "TEST 00:01:01");
        timer.setStatus(ChronoDownTimer::PAUSE);
        timer.timeUpdate();
        QCOMPARE(timer.getString(), "TEST 00:01:01");
        timer.timeUpdate();
        QCOMPARE(timer.getString(), "TEST 00:01:01");
    }

    void resume_chrono_and_update_time_test(){
        ChronoDownTimer timer;
        timer.setFormat("TEST $h:$m:$s");
        timer.setTarget(QTime(0, 1, 2));
        timer.setStatus(ChronoDownTimer::START);
        QCOMPARE(timer.getString(), "TEST 00:01:02");
        timer.timeUpdate();
        QCOMPARE(timer.getString(), "TEST 00:01:01");
        timer.setStatus(ChronoDownTimer::PAUSE);
        timer.timeUpdate();
        QCOMPARE(timer.getString(), "TEST 00:01:01");
        timer.setStatus(ChronoDownTimer::RESUME);
        timer.timeUpdate();
        QCOMPARE(timer.getString(), "TEST 00:01:00");
    }

    void stop_chrono_and_update_time_test(){
        ChronoDownTimer timer;
        timer.setFormat("TEST $h:$m:$s");
        timer.setTarget(QTime(0, 1, 2));
        timer.setStatus(ChronoDownTimer::START);
        QCOMPARE(timer.getString(), "TEST 00:01:02");
        timer.setStatus(ChronoDownTimer::STOP);
        QCOMPARE(timer.getString(), "");
    }

    void setTimeoutMsg_test(){
        ChronoDownTimer timer;
        timer.setTimeoutMsg("TimeOut");
        QCOMPARE(timer.timeoutMsg, "TimeOut");
    }

    void chrono_time_out_test(){
        ChronoDownTimer timer;
        timer.setTimeoutMsg("TimeOut");
        timer.setFormat("TEST $h:$m:$s");
        timer.setTarget(QTime(0, 0, 1));
        timer.setStatus(ChronoDownTimer::START);
        QCOMPARE(timer.getString(), "TEST 00:00:01");
        timer.timeUpdate();
        QCOMPARE(timer.getString(), "TEST 00:00:00");
        timer.timeUpdate();
        QCOMPARE(timer.getString(), "TimeOut");
    }

    void double_digit_switch_test(){
        ChronoDownTimer timer;
        timer.setFormat("TEST $h:$m:$s");
        timer.setTarget(QTime(0, 1, 2));
        timer.setStatus(ChronoDownTimer::START);
        QCOMPARE(timer.getString(), "TEST 00:01:02");
        timer.setDoubleDigit(false);
        QCOMPARE(timer.getString(), "TEST 0:1:2");
    }
};

ADD_TEST(UtChronoDownTimer);
