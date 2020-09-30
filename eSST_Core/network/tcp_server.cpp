#include "tcp_server.h"

TcpServer::TcpServer(QObject *parent):
    QObject(parent){

}

TcpServer::~TcpServer(){
    clearConnection();
    server.close();
}

void TcpServer::setAddress(QString const &address){
    this->address.setAddress(address);
}

void TcpServer::setPort(int port){
    this->port = port;
}

void TcpServer::setPassword(QString const &password){
    this->password = password;
}

bool TcpServer::isReady(){
    return address.protocol() != -1 && port < 65536 && port >= 0;
}

void TcpServer::start(){
    server.listen(address, quint16(port));
    connect(&server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void TcpServer::stop(){
    clearConnection();
    server.close();
    disconnect(&server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

QList<QList<QString>> TcpServer::getAllConnectionInfo() const{
    QList<QList<QString>> result;
    for(int i=0 ; i<connections.size() ; i++){
        QList<QString> row;
        row.push_back(QString::number(i));
        row.push_back(connections[i]->getName());
        row.push_back(connections[i]->getAddress().toString());
        result.push_back(row);
    }
    return result;
}

void TcpServer::someOneDisconnected(){
    auto it = connections.begin();
    while(it != connections.end()){
        if(!(*it)->isConnected()){
            delete (*it);
            it = connections.erase(it);
        }else{
            it++;
        }
    }
    emit(connectionUpdate());
}

void TcpServer::newConnection(){
    QTcpSocket *newSocket = server.nextPendingConnection();
    if(newSocket->waitForReadyRead(1000)){
        QString vMessage = newSocket->readAll();
        QJsonDocument j = QJsonDocument::fromJson(vMessage.toUtf8());
        if(j.isObject() && j[QString("key")].toString() == password){
            TcpConnection *connection = new TcpConnection(j[QString("name")].toString(), newSocket);
            connect(connection, SIGNAL(disconnected()), this, SLOT(someOneDisconnected()));
            connections.push_back(connection);
            emit(connectionUpdate());
            return;
        }
    }
    newSocket->disconnectFromHost();
}

void TcpServer::clearConnection(){
    foreach(TcpConnection *connection, connections){
        delete connection;
    }
    connections.clear();
}
