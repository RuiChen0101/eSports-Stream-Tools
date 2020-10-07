#include <QtTest>
#include "testexec.h"

#include "network/tcp_server.h"
#include "network/tcp_connection.h"

#include <QSignalSpy>

class UtTcpServer : public QObject{
    Q_OBJECT

private slots:
    void setter_test(){
        TcpServer server;
        server.setAddress("127.0.0.1");
        server.setPort(50000);
        server.setPassword("psw");
        QCOMPARE(server.address.toString(), QString("127.0.0.1"));
        QCOMPARE(server.port, 50000);
        QCOMPARE(server.password, QString("psw"));
    }

    void isReady_all_ready_test(){
        TcpServer server;
        server.setAddress("127.0.0.1");
        server.setPort(50000);
        QVERIFY(server.isReady());
    }

    void isReady_invalid_address_test(){
        TcpServer server;
        server.setAddress("127.0.0.1000");
        server.setPort(50000);
        QVERIFY(!server.isReady());
    }

    void isReady_port_less_then_0_test(){
        TcpServer server;
        server.setAddress("127.0.0.1");
        server.setPort(-1);
        QVERIFY(!server.isReady());
    }

    void isReady_port_larger_then_65535_test(){
        TcpServer server;
        server.setAddress("127.0.0.1");
        server.setPort(65536);
        QVERIFY(!server.isReady());
    }

    void kickConnection_test(){
        TcpServer server;
        QSignalSpy logSpy(&server, SIGNAL(logUpdate(QString)));
        QSignalSpy updateSpy(&server, SIGNAL(connectionUpdate()));
        server.connections.push_back(new TcpConnection("test name", new QTcpSocket()));
        server.kickConnection(0);
        QCOMPARE(server.connections.count(), 0);
        QCOMPARE(logSpy.count(), 1);
        QCOMPARE(logSpy.takeFirst().at(0).toString(), QString("test name kicked"));
        QCOMPARE(updateSpy.count(), 1);
    }

    void clearConnection_test(){
        TcpServer server;
        server.connections.push_back(new TcpConnection("test name", new QTcpSocket()));
        server.clearConnection();
        QCOMPARE(server.connections.count(), 0);
    }

    void getAllConnectionInfo_test(){
        TcpServer server;
        server.connections.push_back(new TcpConnection("test name1", new QTcpSocket()));
        server.connections.push_back(new TcpConnection("test name2", new QTcpSocket()));
        QList<QList<QString>> list = server.getAllConnectionInfo();
        QCOMPARE(list[0][0], QString("test name1"));
        QCOMPARE(list[0][1], QString(""));
        QCOMPARE(list[1][0], QString("test name2"));
        QCOMPARE(list[1][1], QString(""));
    }
};

ADD_TEST(UtTcpServer)
