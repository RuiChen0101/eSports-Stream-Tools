#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QString>
#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include <QHostAddress>
#include <QJsonDocument>
#include <QAbstractSocket>

class TcpClient : public QObject{
    Q_OBJECT
public:
    TcpClient(QObject *parent = nullptr);
    ~TcpClient();
    void setAddress(QString const &);
    void setPort(int);
    void setPassword(QString const &);
    void setName(QString const &);
    bool isReady();

public slots:
    void startConnect();
    void stopConnect();
    void stateChanged(QAbstractSocket::SocketState);

signals:
    void stateUpdate(QAbstractSocket::SocketState);
private:
    QHostAddress address;
    QTcpSocket socket;
    QString password;
    QString name;
    int port;
};

#endif // TCPCLIENT_H
