#include <QtTest>
#include "testexec.h"

#include "timer/chronodowntimer.h"

class UtChronoDownTimer : public QObject{
    Q_OBJECT

private slots:
    void getString_with_stop_status(){
        ChronoDownTimer timer;
        QCOMPARE("", timer.getString());
    }

    void setTarget_and_remainSec_test(){
        ChronoDownTimer timer;
        timer.setTarget(QTime(0, 1, 1));
        QCOMPARE(61, timer.remainSec);
    }
};

ADD_TEST(UtChronoDownTimer);
