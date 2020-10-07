#include "network_view.h"
#include "ui_network_view.h"
#include "network/share_config.h"
#include "utility/signal_bus.h"

NetworkView::NetworkView(QWidget *parent) :
    QWidget(parent), ui(new Ui::NetworkView), config("NetworkViewConfig.json"){
    ui->setupUi(this);

    loadConfig();
    initShareConfig();
    connectSignal();
    networkSettingUpdate();
}

NetworkView::~NetworkView(){
    server.stop();
    saveConfig();
    delete ui;
}

void NetworkView::serverLogUpdate(QString log){
    ui->log_display->appendPlainText(log);
}

void NetworkView::serverConnectionUpdate(){
    QList<QList<QString>> data = server.getAllConnectionInfo();
    ui->connection_list->setRowCount(0);
    foreach(QList<QString> const &row, data){
        int count = ui->connection_list->rowCount();
        ui->connection_list->insertRow(count);
        ui->connection_list->setItem(count, 0, new QTableWidgetItem(row[0]));
        ui->connection_list->item(count, 0)->setTextAlignment(Qt::AlignCenter);
        ui->connection_list->setItem(count, 1, new QTableWidgetItem(row[1]));
        ui->connection_list->item(count, 1)->setTextAlignment(Qt::AlignCenter);
    }
}

void NetworkView::networkSettingUpdate(){
    server.setAddress(ui->ip_edit->text());
    server.setPort(ui->port_edit->text().toInt());
    server.setPassword(ui->connect_password_edit->text());
    ui->server_start_btn->setEnabled(server.isReady());
}

void NetworkView::kickConnection(){
    server.kickConnection(ui->connection_list->currentIndex().row());
}

void NetworkView::clearMessage(){
    ui->message_edit->clear();
    ShareConfig::inst()->insert("messages", ui->message_edit->toPlainText());
    ShareConfig::inst()->commit();
}

void NetworkView::sendMessage(){
    ShareConfig::inst()->insert("messages", ui->message_edit->toPlainText());
    ShareConfig::inst()->commit();
}

void NetworkView::startServer(){
    server.start();
    ui->ip_edit->setEnabled(false);
    ui->port_edit->setEnabled(false);
    ui->server_start_btn->setEnabled(false);
    ui->connect_password_edit->setEnabled(false);
}

void NetworkView::stopServer(){
    server.stop();
    ui->server_start_btn->setEnabled(server.isReady());
    ui->ip_edit->setEnabled(true);
    ui->port_edit->setEnabled(true);
    ui->connect_password_edit->setEnabled(true);
    ui->connection_list->setRowCount(0);
}

void NetworkView::clearLog(){
    ui->log_display->clear();
}

void NetworkView::initShareConfig(){
    ShareConfig::inst()->insert("messages", ui->message_edit->toPlainText());
    ShareConfig::inst()->commit();
}

void NetworkView::connectSignal(){
    connect(ui->ip_edit, SIGNAL(textChanged(QString)), this, SLOT(networkSettingUpdate()));
    connect(ui->port_edit, SIGNAL(textChanged(QString)), this, SLOT(networkSettingUpdate()));
    connect(ui->connect_password_edit, SIGNAL(textChanged(QString)), this, SLOT(networkSettingUpdate()));

    connect(ui->server_start_btn, SIGNAL(clicked(bool)), this, SLOT(startServer()));
    connect(ui->server_stop_btn, SIGNAL(clicked(bool)), this, SLOT(stopServer()));

    connect(ui->connection_kick_btn, SIGNAL(clicked(bool)), this, SLOT(kickConnection()));

    connect(ui->clear_log_btn, SIGNAL(clicked(bool)), this, SLOT(clearLog()));

    connect(ui->send_message_btn, SIGNAL(clicked(bool)), this, SLOT(sendMessage()));
    connect(ui->clear_message_btn, SIGNAL(clicked(bool)), this, SLOT(clearMessage()));

    connect(&server, SIGNAL(connectionUpdate()), this, SLOT(serverConnectionUpdate()));
    connect(&server, SIGNAL(logUpdate(QString)), this, SLOT(serverLogUpdate(QString)));
    connect(ShareConfig::inst(), SIGNAL(configUpdate(QString)), &server, SLOT(broadcastMessage(QString)));
}

void NetworkView::loadConfig(){
    if(config.loadFile()){
        try{
            ui->ip_edit->setText(config.read("server_address").toString());
            ui->port_edit->setText(config.read("server_port").toString());
            ui->connect_password_edit->setText(config.read("server_password").toString());
            ui->message_edit->setPlainText(config.read("messages").toString());
        }catch(std::runtime_error &e){
            emit(SignalBus::inst()->systemMessageEvent("NetworkView load config fail"));
        }
    }else{
        emit(SignalBus::inst()->systemMessageEvent("NetworkView load config fail"));
    }
}

void NetworkView::saveConfig(){
    config.insert("server_address", ui->ip_edit->text());
    config.insert("server_port", ui->port_edit->text());
    config.insert("server_password", ui->connect_password_edit->text());
    config.insert("messages", ui->message_edit->toPlainText());
}
