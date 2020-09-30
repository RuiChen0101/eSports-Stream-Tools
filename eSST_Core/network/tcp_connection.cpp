#include "tcp_connection.h"

TcpConnection::TcpConnection(QString const &name, QTcpSocket *socket, QObject *parent):
    QObject(parent), socket(socket), name(name){

    connect(socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(newMessage()));
}

TcpConnection::~TcpConnection(){
    disconnect(socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
    stopConnect();
}

QString TcpConnection::getName() const{
    return name;
}

QHostAddress TcpConnection::getAddress() const{
    return socket->peerAddress();
}

void TcpConnection::stopConnect(){
    if(socket->state() == QAbstractSocket::ConnectedState || socket->state() == QAbstractSocket::ConnectingState){
        socket->disconnectFromHost();
    }
}

bool TcpConnection::isConnected(){
    return socket->state() == QAbstractSocket::ConnectedState;
}

void TcpConnection::newMessage(){
    qDebug() << socket->readAll();
}
