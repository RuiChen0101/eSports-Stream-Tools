#include <QtTest>
#include "testexec.h"

#include "file/file_source.h"

#include <QDir>
#include <QSignalSpy>

class UtFileSource : public QObject{
    Q_OBJECT

private slots:
    void isOutputing_test(){
        FileSource source;
        QVERIFY(source.isOutputing());
    }

    void setString_and_getString_test(){
        FileSource source;
        QSignalSpy spy(&source, SIGNAL(contentUpdate()));
        QVERIFY(spy.isValid());
        source.setString("test");
        QCOMPARE(spy.count(), 1);
        QCOMPARE(source.getString(), "test");
    }
};

ADD_TEST(UtFileSource)
