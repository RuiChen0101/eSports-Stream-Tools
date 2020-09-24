#include <QtTest>
#include "testexec.h"

#include "file/file.h"
#include "fake_file_source.h"

#include <QDir>
#include <QFile>

class UtFile : public QObject{
    Q_OBJECT

private slots:
    void initTestCase(){
        testFolder.setPath(QDir::currentPath() + "/TestFiles");
        if(!testFolder.exists()){
            testFolder.mkdir(".");
        }
        if(testFolder.exists(testFile)){
            testFolder.remove(testFile);
        }
        testFilePath = testFolder.filePath(testFile);
        QVERIFY(testFolder.exists());
    }

    void construct_with_source_not_outputing_test(){
        FakeFileSource source;
        source.setString("test");
        source.setOutputing(false);
        File file(&source, testFilePath);
        QCOMPARE(file.readAll(), "");
    }

    void construct_with_source_outputing_test(){
        FakeFileSource source;
        source.setString("test");
        source.setOutputing(true);
        File file(&source, testFilePath);
        QCOMPARE(file.readAll(), "test");
    }

    void destructor_test(){
        {
            FakeFileSource source;
            source.setString("test");
            source.setOutputing(true);
            File file(&source, testFilePath);
            QCOMPARE(file.readAll(), "test");
        }
        QFile file(testFolder.filePath(testFile));
        QCOMPARE(file.size(), 0);
    }

    void getFilePath_test(){
        FakeFileSource source;
        File file(&source, testFilePath);
        QCOMPARE(file.getFilePath(), testFilePath);
    }

    void file_source_update_test(){
        FakeFileSource source;
        source.setString("test");
        source.setOutputing(true);
        File file(&source, testFilePath);
        QCOMPARE(file.readAll(), "test");
        source.setString("test2");
        QCOMPARE(file.readAll(), "test2");
    }

    void change_file_source_test(){
        FakeFileSource source1;
        source1.setString("test");
        source1.setOutputing(true);
        FakeFileSource source2;
        source2.setString("test2");
        source2.setOutputing(true);
        File file(&source1, testFilePath);
        QCOMPARE(file.readAll(), "test");
        file.setFileSource(&source2);
        QCOMPARE(file.readAll(), "test2");
    }

    void cleanup(){
        if(testFolder.exists(testFile)){
            testFolder.remove(testFile);
        }
    }

    void cleanupTestCase(){
        if(testFolder.exists()){
            testFolder.rmdir(".");
        }
    }
private:
    QDir testFolder;
    QString testFilePath;
    const QString testFile ="TestFile";
};

ADD_TEST(UtFile)
