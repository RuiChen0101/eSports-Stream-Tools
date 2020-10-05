#include <QtTest>
#include "testexec.h"

#include "file/config_file.h"
#include "file/file_manager.h"

#include <QDir>
#include <QFile>

class UtConfigFile : public QObject{
    Q_OBJECT

private slots:
    void initTestCase(){
        configDir = FileManager::inst()->getConfigFileDir();
    }

    void constructor_test(){
        ConfigFile config(testFile);
        QCOMPARE(config.file.fileName(), configDir.filePath(testFile));
    }

    void insert_and_read_test(){
        ConfigFile config(testFile);
        config.insert("string", "test string");
        config.insert("int", 1);
        config.insert("bool", true);
        QCOMPARE(config.read("string").toString(), QString("test string"));
        QCOMPARE(config.read("int").toInt(), 1);
        QCOMPARE(config.read("bool").toBool(), true);
    }

    void read_not_exist_key_throw_test(){
        ConfigFile config(testFile);
        QVERIFY_EXCEPTION_THROWN(config.read("not_exist_key"), std::runtime_error);
    }

    void loadFile_not_exist_text(){
        ConfigFile config(testFile);
        QVERIFY(!config.file.exists());
        QVERIFY(!config.loadFile());
    }

    void loadFile_not_json_object_text(){
        QFile file(configDir.filePath(testFile));
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        file.write("not json");
        file.close();
        ConfigFile config(testFile);
        QVERIFY(config.file.exists());
        QVERIFY(!config.loadFile());
    }

    void saveFile_text(){
        ConfigFile config(testFile);
        config.insert("string", "test string");
        config.insert("int", 1);
        config.saveFile();
        QFile file(configDir.filePath(testFile));
        file.open(QIODevice::ReadOnly);
        QString savedString = file.readAll();
        file.close();
        QCOMPARE(savedString, QString("{\"int\":1,\"string\":\"test string\"}"));
    }

    void cleanup(){
        configDir.remove(testFile);
    }

    void cleanupTestCase(){
        configDir.removeRecursively();
    }
private:
    QDir configDir;
    const QString testFile = "testFile.json";
};

ADD_TEST(UtConfigFile)
