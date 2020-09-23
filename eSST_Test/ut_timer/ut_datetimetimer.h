#include <QtTest>
#include <QDateTime>
#include "testexec.h"

#include "timer/date_time_timer.h"

class UtDateTimeTimer : public QObject{
    Q_OBJECT

private slots:
    void isOutputing_test(){
        DateTimeTimer timer;
        QVERIFY(timer.isOutputing());
    }
};

ADD_TEST(UtDateTimeTimer);
