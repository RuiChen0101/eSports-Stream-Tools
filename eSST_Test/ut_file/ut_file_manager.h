#include <QtTest>
#include "testexec.h"

#include "fake_file_source.h"
#include "file/file_manager.h"

#include <QDir>

class UtFileManager : public QObject{
    Q_OBJECT

private slots:
    void constructor_test(){
        QVERIFY(manager.getTimerFileDir().exists());
        QVERIFY(manager.getScoreFileDir().exists());
        QVERIFY(manager.getConfigFileDir().exists());
    }

    void prepare_folder_test(){
        manager.prepareFolder(QDir::currentPath() + "TestFolder");
        QDir dir(QDir::currentPath() + "TestFolder");
        QVERIFY(dir.exists());
    }

    void registeFile_and_change_source_test(){
        FakeFileSource source1;
        source1.setString("test");
        source1.setOutputing(true);
        FakeFileSource source2;
        source2.setString("test2");
        source2.setOutputing(true);
        manager.registeFile(&source1, manager.getTimerFileDir(), testFile);
        QVERIFY(manager.getTimerFileDir().exists(testFile));
        QCOMPARE(manager.files[testFile]->readAll(), QString("test"));
        manager.registeFile(&source2, manager.getTimerFileDir(), testFile);
        QCOMPARE(manager.files[testFile]->readAll(), QString("test2"));
    }

    void registeTimerFile_test(){
        FakeFileSource source;
        source.setString("test");
        source.setOutputing(true);
        manager.registeTimerFile(&source, testFile);
        QVERIFY(manager.getTimerFileDir().exists(testFile));
        QCOMPARE(manager.files[testFile]->readAll(), QString("test"));
    }

    void registeScoreFile_test(){
        FakeFileSource source;
        source.setString("test");
        source.setOutputing(true);
        manager.registeScoreFile(&source, testFile);
        QVERIFY(manager.getScoreFileDir().exists(testFile));
        QCOMPARE(manager.files[testFile]->readAll(), QString("test"));
    }

    void getFilePathByName_test(){
        FakeFileSource source;
        source.setString("test");
        source.setOutputing(true);
        manager.registeScoreFile(&source, testFile);
        QCOMPARE(manager.getFilePathByName(testFile), manager.getScoreFileDir().filePath(testFile));
    }

    void deregisteFile_test(){
        FakeFileSource source;
        source.setString("test");
        source.setOutputing(true);
        manager.registeTimerFile(&source, testFile);
        QVERIFY(manager.getTimerFileDir().exists(testFile));
        QCOMPARE(manager.files[testFile]->readAll(), QString("test"));
        manager.deregisteFile(testFile);
        QVERIFY(!manager.files.contains(testFile));
        QFile file(manager.getTimerFileDir().filePath(testFile));
        QCOMPARE(file.size(), 0);
    }

    void cleanup(){
        manager.deregisteFile(testFile);
    }

    void cleanupTestCase(){
        manager.getTimerFileDir().removeRecursively();
        manager.getScoreFileDir().removeRecursively();
        manager.getConfigFileDir().removeRecursively();
        QDir dir(QDir::currentPath() + "TestFolder");
        dir.removeRecursively();
    }
private:
    FileManager manager;
    const QString testFile ="TestFile";
};

ADD_TEST(UtFileManager)
