#include "tcp_client.h"

TcpClient::TcpClient(QObject *parent):
    QObject(parent), name(""){
    connect(&socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
}

TcpClient::~TcpClient(){
    stopConnect();
}

void TcpClient::setAddress(QString const &address){
    this->address.setAddress(address);
}

void TcpClient::setPort(int port){
    this->port = port;
}

void TcpClient::setPassword(QString const &password){
    this->password = password;
}

void TcpClient::setName(QString const &name){
    this->name = name;
}

bool TcpClient::isReady(){
    return address.protocol() != -1 && port < 65536 && port >= 0 && name != "";
}

void TcpClient::startConnect(){
    socket.connectToHost(address, port);
    if(socket.waitForConnected(1000)){
        QJsonObject j;
        j.insert(QString("name"), name);
        j.insert(QString("key"), password);
        QString data = QJsonDocument(j).toJson(QJsonDocument::Compact);
        socket.write(data.toUtf8());
    }
}

void TcpClient::stopConnect(){
    if(socket.state() == QAbstractSocket::ConnectedState || socket.state() == QAbstractSocket::ConnectingState){
        socket.disconnectFromHost();
    }
}

void TcpClient::stateChanged(QAbstractSocket::SocketState state){
    emit(stateUpdate(state));
}
