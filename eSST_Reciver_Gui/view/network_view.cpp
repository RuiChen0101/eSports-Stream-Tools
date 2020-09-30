#include "network_view.h"
#include "ui_network_view.h"
#include "utility/signal_bus.h"

NetworkView::NetworkView(QWidget *parent) :
    QWidget(parent), ui(new Ui::NetworkView){
    ui->setupUi(this);

    connectSignal();
    networkSettingUpdate();
}

NetworkView::~NetworkView(){
    delete ui;
}

void NetworkView::networkSettingUpdate(){
    client.setName(ui->name_edit->text());
    client.setAddress(ui->ip_edit->text());
    client.setPort(ui->port_edit->text().toInt());
    client.setPassword(ui->connect_password_edit->text());
    ui->connect_btn->setEnabled(client.isReady());
}

void NetworkView::socketStateUpdate(QAbstractSocket::SocketState state){
    switch(state){
        case QAbstractSocket::HostLookupState:
        case QAbstractSocket::ConnectingState:
            emit(SignalBus::inst()->systemMessageEvent("connecting..."));
            ui->ip_edit->setEnabled(false);
            ui->name_edit->setEnabled(false);
            ui->port_edit->setEnabled(false);
            ui->connect_btn->setEnabled(false);
            ui->connect_password_edit->setEnabled(false);
            break;
        case QAbstractSocket::ConnectedState:
            emit(SignalBus::inst()->systemMessageEvent("connected!!"));
            break;
        default:
            emit(SignalBus::inst()->systemMessageEvent("disconnected!!"));
            ui->connect_btn->setEnabled(client.isReady());
            ui->ip_edit->setEnabled(true);
            ui->name_edit->setEnabled(true);
            ui->port_edit->setEnabled(true);
            ui->connect_password_edit->setEnabled(true);
            break;
    }
}

void NetworkView::connectSignal(){
    connect(ui->ip_edit, SIGNAL(textChanged(QString)), this, SLOT(networkSettingUpdate()));
    connect(ui->port_edit, SIGNAL(textChanged(QString)), this, SLOT(networkSettingUpdate()));
    connect(ui->name_edit, SIGNAL(textChanged(QString)), this, SLOT(networkSettingUpdate()));
    connect(ui->connect_password_edit, SIGNAL(textChanged(QString)), this, SLOT(networkSettingUpdate()));

    connect(ui->connect_btn, SIGNAL(clicked(bool)), &client, SLOT(startConnect()));
    connect(ui->disconnect_btn, SIGNAL(clicked(bool)), &client, SLOT(stopConnect()));

    connect(&client, SIGNAL(stateUpdate(QAbstractSocket::SocketState)), this, SLOT(socketStateUpdate(QAbstractSocket::SocketState)));
}
