#include <QtTest>
#include "testexec.h"

#include "timer/timerformatparser.h"

class UtTimerFormatParser : public QObject{
    Q_OBJECT

private slots:
    void StTimeUnit_fromSecond_test(){
        StTimeUnit timeUnit;
        timeUnit.fromSecond(90061);
        QCOMPARE(1, timeUnit.sec);
        QCOMPARE(1, timeUnit.min);
        QCOMPARE(1, timeUnit.hour);
        QCOMPARE(1, timeUnit.day);
    }

    void setter_test(){
        TimerFormatParser parser;
        parser.setFormat("$h:$m:$s");
        parser.setSecond(59);
        QCOMPARE("$h:$m:$s", parser.format);
        QCOMPARE(59, parser.timeUnit.sec);
    }

    void getString_single_digit_test_1(){
        TimerFormatParser parser;
        parser.setFormat("TEST $d:$h:$m:$s");
        parser.setSecond(90061);
        QCOMPARE("TEST 1:1:1:1", parser.getString());
    }

    void getString_single_digit_test_2(){
        TimerFormatParser parser;
        parser.setFormat("$s:$m:$h:$d $d:$h:$m:$s");
        parser.setSecond(93784);
        QCOMPARE("4:3:2:1 1:2:3:4", parser.getString());
    }

    void getString_double_digit_test_1(){
        TimerFormatParser parser;
        parser.setDoubleDigit(true);
        parser.setFormat("TEST $d:$h:$m:$s");
        parser.setSecond(90061);
        QCOMPARE("TEST 01:01:01:01", parser.getString());
    }

    void getString_double_digit_test_2(){
        TimerFormatParser parser;
        parser.setDoubleDigit(true);
        parser.setFormat("$s:$m:$h:$d $d:$h:$m:$s");
        parser.setSecond(93784);
        QCOMPARE("04:03:02:01 01:02:03:04", parser.getString());
    }
};

ADD_TEST(UtTimerFormatParser);
