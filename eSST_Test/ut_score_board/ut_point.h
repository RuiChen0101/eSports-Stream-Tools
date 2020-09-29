#include <QtTest>
#include "testexec.h"

#include "score_board/point.h"
#include <QSignalSpy>

class UtPoint : public QObject{
    Q_OBJECT

private slots:
    void isOutputing_test(){
        Point points;
        QVERIFY(points.isOutputing());
    }

    void getPoint_and_getString_test(){
        Point points;
        QCOMPARE(points.getPoint(), qint8(0));
        QCOMPARE(points.getString(), QString("0"));
    }

    void addPoint_test(){
        Point points;
        QSignalSpy spy(&points, SIGNAL(contentUpdate()));
        points.addPoint(1);
        QCOMPARE(spy.count(), 1);
        QCOMPARE(points.getPoint(), qint8(1));
        QCOMPARE(points.getString(), QString("1"));
    }

    void reset_test(){
        Point points;
        points.addPoint(1);
        QCOMPARE(points.getPoint(), qint8(1));
        QCOMPARE(points.getString(), QString("1"));
        QSignalSpy spy(&points, SIGNAL(contentUpdate()));
        points.reset();
        QCOMPARE(spy.count(), 1);
        QCOMPARE(points.getPoint(), qint8(0));
        QCOMPARE(points.getString(), QString("0"));
    }
};

ADD_TEST(UtPoint)
