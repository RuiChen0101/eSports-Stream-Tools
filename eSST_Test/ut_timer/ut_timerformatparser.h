#include <QtTest>
#include "testexec.h"

#include "timer/timer_format_parser.h"

class UtTimerFormatParser : public QObject{
    Q_OBJECT

private slots:
    void StTimeUnit_fromSecond_test(){
        StTimeUnit timeUnit;
        timeUnit.fromSecond(90061);
        QCOMPARE(timeUnit.sec, quint8(1));
        QCOMPARE(timeUnit.min, quint8(1));
        QCOMPARE(timeUnit.hour, quint8(1));
        QCOMPARE(timeUnit.day, quint8(1));
    }

    void setter_test(){
        TimerFormatParser parser;
        parser.setFormat("$h:$m:$s");
        parser.setSecond(61);
        QCOMPARE(parser.format, QString("$h:$m:$s"));
        QCOMPARE(parser.timeUnit.sec, quint8(1));
        QCOMPARE(parser.timeUnit.min, quint8(1));
        QCOMPARE(parser.timeUnit.hour, quint8(0));
        QCOMPARE(parser.timeUnit.day, quint8(0));
    }

    void numberToString_single_digit(){
        TimerFormatParser parser;
        QCOMPARE(parser.numberToString(1), QString("1"));
        QCOMPARE(parser.numberToString(11), QString("11"));
    }

    void numberToString_double_digit(){
        TimerFormatParser parser;
        parser.setDoubleDigit(true);
        QCOMPARE(parser.numberToString(1), QString("01"));
        QCOMPARE(parser.numberToString(11), QString("11"));
    }

    void getString_single_digit_test_1(){
        TimerFormatParser parser;
        parser.setFormat("TEST $d:$h:$m:$s");
        parser.setSecond(90061);
        QCOMPARE(parser.getString(), QString("TEST 1:1:1:1"));
    }

    void getString_single_digit_test_2(){
        TimerFormatParser parser;
        parser.setFormat("$s:$m:$h:$d $d:$h:$m:$s");
        parser.setSecond(93784);
        QCOMPARE(parser.getString(), QString("4:3:2:1 1:2:3:4"));
    }

    void getString_double_digit_test_1(){
        TimerFormatParser parser;
        parser.setDoubleDigit(true);
        parser.setFormat("TEST $d:$h:$m:$s");
        parser.setSecond(90061);
        QCOMPARE(parser.getString(), QString("TEST 01:01:01:01"));
    }

    void getString_double_digit_test_2(){
        TimerFormatParser parser;
        parser.setDoubleDigit(true);
        parser.setFormat("$s:$m:$h:$d $d:$h:$m:$s");
        parser.setSecond(93784);
        QCOMPARE(parser.getString(), QString("04:03:02:01 01:02:03:04"));
    }

    void getString_mixing_test(){
        TimerFormatParser parser;
        parser.setFormat("$dA$hB$mC$s");
        parser.setSecond(93784);
        QCOMPARE(parser.getString(), QString("1A2B3C4"));
    }
};

ADD_TEST(UtTimerFormatParser);
