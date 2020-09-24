#include <QtTest>
#include "testexec.h"

#include "fake_file_source.h"
#include "file/file_manager.h"

#include <QDir>

class UtFileManager : public QObject{
    Q_OBJECT

private slots:
    void initTestCase(){
        textFolder = manager.getTextFileDir();
    }

    void constructor_test(){
        QVERIFY(manager.getTextFileDir().exists());
        QVERIFY(manager.getConfigFileDir().exists());
    }

    void prepare_folder_test(){
        manager.prepareFolder(QDir::currentPath() + "TestFolder");
        QDir dir(QDir::currentPath() + "TestFolder");
        QVERIFY(dir.exists());
    }

    void registeTextFile_and_change_source_test(){
        FakeFileSource source1;
        source1.setString("test");
        source1.setOutputing(true);
        FakeFileSource source2;
        source2.setString("test2");
        source2.setOutputing(true);
        manager.registeTextFile(&source1, testFile);
        QVERIFY(textFolder.exists(testFile));
        QCOMPARE(manager.files[testFile]->readAll(), "test");
        manager.registeTextFile(&source2, testFile);
        QCOMPARE(manager.files[testFile]->readAll(), "test2");
    }

    void deregisteTextFile_test(){
        manager.deregisteTextFile(testFile);
        QVERIFY(!manager.files.contains(testFile));
        QFile file(textFolder.filePath(testFile));
        QCOMPARE(file.size(), 0);
    }

    void cleanupTestCase(){
        if(manager.getTextFileDir().exists()){
            manager.getTextFileDir().rmdir(".");
        }
        if(manager.getConfigFileDir().exists()){
            manager.getConfigFileDir().rmdir(".");
        }
        QDir dir(QDir::currentPath() + "TestFolder");
        if(dir.exists()){
            dir.rmdir(".");
        }
    }
private:
    FileManager manager;
    QDir textFolder;
    const QString testFile ="TestFile";
};

ADD_TEST(UtFileManager)
