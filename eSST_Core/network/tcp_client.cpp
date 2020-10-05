#include "tcp_client.h"
#include "utility/config.h"

TcpClient::TcpClient(QObject *parent):
    QObject(parent), name(""){
    connect(&socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    connect(&socket, SIGNAL(readyRead()), this, SLOT(newMessage()));
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
    return address.protocol() != -1 && port <= 65535 && port >= 0 && name != "";
}

void TcpClient::send(QString const &message){
    qDebug() << message;
    if(socket.state() == QAbstractSocket::ConnectedState){
        socket.write(message.toUtf8());
    }
}

void TcpClient::forceSync(){
    send("sync");
}

void TcpClient::stopConnect(){
    if(socket.state() == QAbstractSocket::ConnectedState || socket.state() == QAbstractSocket::ConnectingState){
        socket.disconnectFromHost();
    }
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

void TcpClient::stateChanged(QAbstractSocket::SocketState state){
    emit(stateUpdate(state));
}

void TcpClient::newMessage(){
    QString message = socket.readAll();
    qDebug()<<message;
    Config::inst()->insert(message);
    Config::inst()->commit();
}
