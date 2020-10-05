#include <QtTest>
#include "testexec.h"

#include "utility/config.h"
#include "file/file_manager.h"

#include <QDir>
#include <QFile>

class UtConfig : public QObject{
    Q_OBJECT

private slots:
    void initTestCase(){
        configDir = FileManager::inst()->getConfigFileDir();
    }

    void constructor_test(){
        Config config;
        QCOMPARE(config.file.fileName(), configDir.filePath(Config::fileName));
    }

    void merge_json_object_test(){
        Config config;
        QJsonObject j1, j2;
        j1["string"] = "test";
        j1["int"] = 1;
        j2["string"] = "test string";
        j2["bool"] = true;
        QJsonObject merged = config.mergeObject(j1, j2);
        QCOMPARE(merged["string"].toString(), QString("test string"));
        QCOMPARE(merged["int"].toInt(), 1);
        QCOMPARE(merged["bool"].toBool(), true);
    }

    void insert_buffer_test(){
        Config config;
        config.insert("string", "test string");
        config.insert("int", 1);
        config.insert("bool", true);
        QCOMPARE(config.buffer["string"].toString(), QString("test string"));
        QCOMPARE(config.buffer["int"].toInt(), 1);
        QCOMPARE(config.buffer["bool"].toBool(), true);
    }

    void insert_commit_and_read_test(){
        Config config;
        config.insert("string", "test string");
        config.insert("int", 1);
        config.insert("bool", true);
        config.commit();
        QCOMPARE(config.read("string").toString(), QString("test string"));
        QCOMPARE(config.read("int").toInt(), 1);
        QCOMPARE(config.read("bool").toBool(), true);
    }

    void insert_by_string_test(){
        Config config;
        config.insert("string", "test string");
        config.insert("int", 1);
        config.insert("bool", true);
        config.insert("{\"messages\":\"test\"}");
        config.commit();
        QCOMPARE(config.read("string").toString(), QString("test string"));
        QCOMPARE(config.read("int").toInt(), 1);
        QCOMPARE(config.read("bool").toBool(), true);
        QCOMPARE(config.read("messages").toString(), QString("test"));
    }

    void read_not_exist_key_throw_test(){
        Config config;
        QVERIFY_EXCEPTION_THROWN(config.read("not_exist_key"), std::runtime_error);
    }

    void loadFile_not_exist_text(){
        Config config;
        QVERIFY(!config.file.exists());
        QVERIFY(!config.loadFile());
        QVERIFY(!config.isLoaded());
    }

    void loadFile_not_json_object_text(){
        QFile file(configDir.filePath(Config::fileName));
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        file.write("not json");
        file.close();
        Config config;
        QVERIFY(config.file.exists());
        QVERIFY(!config.loadFile());
        QVERIFY(!config.isLoaded());
    }

    void loadFile_success_text(){
        QFile file(configDir.filePath(Config::fileName));
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        file.write("{\"int\":1,\"string\":\"test string\"}");
        file.close();
        Config config;
        QVERIFY(config.file.exists());
        QVERIFY(config.loadFile());
        QVERIFY(config.isLoaded());
    }

    void saveFile_text(){
        Config config;
        config.insert("string", "test string");
        config.insert("int", 1);
        config.commit();
        config.saveFile();
        QFile file(configDir.filePath(Config::fileName));
        file.open(QIODevice::ReadOnly);
        QString savedString = file.readAll();
        file.close();
        QCOMPARE(savedString, QString("{\"int\":1,\"string\":\"test string\"}"));
    }

    void cleanup(){
        configDir.remove(Config::fileName);
    }

    void cleanupTestCase(){
        configDir.removeRecursively();
    }
private:
    QDir configDir;
};

ADD_TEST(UtConfig)
