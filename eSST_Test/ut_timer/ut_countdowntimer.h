#include <QtTest>
#include <QDateTime>
#include "testexec.h"

#include "timer/countdowntimer.h"

class UtCountDownTimer : public QObject{
    Q_OBJECT

private slots:
    void setTarget_and_remainSec_test(){
        CountDownTimer timer;
        timer.setTarget(QDateTime::currentDateTime().addSecs(62));
        QCOMPARE(timer.remainSec, 61);
    }

    void setFormat_test(){
        CountDownTimer timer;
        timer.setFormat("TEST");
        QCOMPARE(timer.parser.getString(), "TEST");
    }

    void start_countdown_and_update_time_test(){
        CountDownTimer timer;
        timer.setFormat("TEST $h:$m:$s");
        timer.remainSec = 62;
        timer.setStatus(CountDownTimer::START);
        QCOMPARE(timer.getString(), "TEST 00:01:02");
        timer.timeUpdate();
        QCOMPARE(timer.getString(), "TEST 00:01:01");
        timer.timeUpdate();
        QCOMPARE(timer.getString(), "TEST 00:01:00");
        timer.timeUpdate();
        QCOMPARE(timer.getString(), "TEST 00:00:59");
    }

    void stop_countdown_and_update_time_test(){
        CountDownTimer timer;
        timer.setFormat("TEST $h:$m:$s");
        timer.remainSec = 62;
        timer.setStatus(CountDownTimer::START);
        QCOMPARE(timer.getString(), "TEST 00:01:02");
        timer.setStatus(CountDownTimer::STOP);
        QCOMPARE(timer.getString(), "");
    }

    void setTimeoutMsg_test(){
        CountDownTimer timer;
        timer.setTimeoutMsg("TimeOut");
        QCOMPARE(timer.timeoutMsg, "TimeOut");
    }

    void chrono_time_out_test(){
        CountDownTimer timer;
        timer.setTimeoutMsg("TimeOut");
        timer.setFormat("TEST $h:$m:$s");
        timer.remainSec = 1;
        timer.setStatus(CountDownTimer::START);
        QCOMPARE(timer.getString(), "TEST 00:00:01");
        timer.timeUpdate();
        QCOMPARE(timer.getString(), "TEST 00:00:00");
        timer.timeUpdate();
        QCOMPARE(timer.getString(), "TimeOut");
    }

    void double_digit_switch_test(){
        CountDownTimer timer;
        timer.setFormat("TEST $h:$m:$s");
        timer.remainSec = 62;
        timer.setStatus(CountDownTimer::START);
        QCOMPARE(timer.getString(), "TEST 00:01:02");
        timer.setDoubleDigit(false);
        QCOMPARE(timer.getString(), "TEST 0:1:2");
    }
};

ADD_TEST(UtCountDownTimer);
