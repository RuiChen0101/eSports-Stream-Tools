#include <QtTest>
#include "testexec.h"

#include "network/tcp_client.h"

class UtTcpClient : public QObject{
    Q_OBJECT

private slots:
    void setter_test(){
        TcpClient client;
        client.setAddress("127.0.0.1");
        client.setPort(50000);
        client.setPassword("psw");
        client.setName("test");
        QCOMPARE(client.address.toString(), QString("127.0.0.1"));
        QCOMPARE(client.port, 50000);
        QCOMPARE(client.password, QString("psw"));
        QCOMPARE(client.name, QString("test"));
    }

    void isReady_all_ready_test(){
        TcpClient client;
        client.setAddress("127.0.0.1");
        client.setPort(50000);
        client.setName("test");
        QVERIFY(client.isReady());
    }

    void isReady_invalid_address_test(){
        TcpClient client;
        client.setAddress("127.0.0.1000");
        client.setPort(50000);
        client.setName("test");
        QVERIFY(!client.isReady());
    }

    void isReady_port_less_then_0_test(){
        TcpClient client;
        client.setAddress("127.0.0.1");
        client.setPort(-1);
        client.setName("test");
        QVERIFY(!client.isReady());
    }

    void isReady_port_larger_then_65535_test(){
        TcpClient client;
        client.setAddress("127.0.0.1");
        client.setPort(65536);
        client.setName("test");
        QVERIFY(!client.isReady());
    }

    void isReady_name_not_set_test(){
        TcpClient client;
        client.setAddress("127.0.0.1");
        client.setPort(50000);
        QVERIFY(!client.isReady());
    }
};

ADD_TEST(UtTcpClient)
