#include <QtTest>
#include "testexec.h"

#include "network/share_config.h"

#include <QSignalSpy>

class UtShareConfig : public QObject{
    Q_OBJECT

private slots:
    void constructor_test(){
        ShareConfig config;
        QVERIFY(config.buffer.isEmpty());
    }

    void merge_json_object_test(){
        ShareConfig config;
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
        ShareConfig config;
        config.insert("string", "test string");
        config.insert("int", 1);
        config.insert("bool", true);
        QCOMPARE(config.buffer["string"].toString(), QString("test string"));
        QCOMPARE(config.buffer["int"].toInt(), 1);
        QCOMPARE(config.buffer["bool"].toBool(), true);
    }

    void insert_commit_and_read_test(){
        ShareConfig config;
        config.insert("string", "test string");
        config.insert("int", 1);
        config.insert("bool", true);
        config.commit();
        QCOMPARE(config.read("string").toString(), QString("test string"));
        QCOMPARE(config.read("int").toInt(), 1);
        QCOMPARE(config.read("bool").toBool(), true);
    }

    void commit_signal_test(){
        ShareConfig config;
        QSignalSpy spy(&config, SIGNAL(configUpdate(QString)));
        config.insert("int", 1);
        config.insert("bool", true);
        config.commit();
        QCOMPARE(spy.count(), 1);
        QCOMPARE(spy.takeFirst().at(0).toString(), QString("{\"bool\":true,\"int\":1}"));
    }

    void insert_by_string_test(){
        ShareConfig config;
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
        ShareConfig config;
        QVERIFY_EXCEPTION_THROWN(config.read("not_exist_key"), std::runtime_error);
    }
};

ADD_TEST(UtShareConfig)
