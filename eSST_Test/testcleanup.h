#include <QtTest>
#include "testexec.h"

#include "file/file_manager.h"

#include <QDir>

class TestCleanup : public QObject{
    Q_OBJECT

private slots:
    void cleanupTestCase(){
        QDir dir = FileManager::inst()->getRootDir();
        dir.removeRecursively();
        QVERIFY(!dir.exists());
    }
};
