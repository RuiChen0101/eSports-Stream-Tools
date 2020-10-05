#include "tcp_connection.h"
#include "utility/config.h"

TcpConnection::TcpConnection(QString const &name, QTcpSocket *socket, QObject *parent):
    QObject(parent), socket(socket), name(name){

    connect(socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(newMessage()));
    send(Config::inst()->getConfigString());
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
    socket->disconnectFromHost();
}

bool TcpConnection::isConnected(){
    return socket->state() == QAbstractSocket::ConnectedState;
}

void TcpConnection::send(QString const &message){
    if(isConnected()){
        socket->write(message.toUtf8());
    }
}

void TcpConnection::newMessage(){
    QString message = socket->readAll();
    if(message == "sync"){
        send(Config::inst()->getConfigString());
    }
}
