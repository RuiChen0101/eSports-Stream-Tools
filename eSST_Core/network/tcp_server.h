#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "tcp_connection.h"

#include <QList>
#include <QObject>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QHostAddress>
#include <QJsonDocument>

class TcpServer : public QObject{
    Q_OBJECT

public:
    TcpServer(QObject * = nullptr);
    ~TcpServer();
    void setAddress(QString const &);
    void setPort(int);
    void setPassword(QString const &);
    void kickConnection(int);
    QList<QList<QString>> getAllConnectionInfo() const;
    bool isReady();

public slots:
    void broadcastMessage(QString);
    void start();
    void stop();

private slots:
    void newConnection();
    void someOneDisconnected();

signals:
    void connectionUpdate();
    void logUpdate(QString);

private:
    void clearConnection();
    QList<TcpConnection*> connections;
    QHostAddress address;
    QTcpServer server;
    QString password;
    int port;
};

#endif // TCPSERVER_H
