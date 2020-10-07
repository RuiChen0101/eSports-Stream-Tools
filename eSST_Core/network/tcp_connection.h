#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QString>
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

class TcpConnection : public QObject{
    Q_OBJECT

public:
    TcpConnection(QString const &, QTcpSocket*, QObject * = nullptr);
    ~TcpConnection();
    QString getName() const;
    QHostAddress getAddress() const;
    void stopConnect();
    bool isConnected();
    void send(QString const &);

private slots:
    void newMessage();

signals:
    void disconnected();

private:
    QTcpSocket *socket;
    QString name;
};

#endif // TCPCONNECTION_H
