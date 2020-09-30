#include "network_view.h"
#include "ui_network_view.h"

NetworkView::NetworkView(QWidget *parent) :
    QWidget(parent), ui(new Ui::NetworkView){
    ui->setupUi(this);

    connectSignal();

    networkSettingUpdate();
}

NetworkView::~NetworkView(){
    delete ui;
    server.stop();
}

void NetworkView::serverStatusUpdate(QString log){
    ui->log_display->appendPlainText(log+"\n");
}

void NetworkView::serverConnectionUpdate(){
    QList<QList<QString>> data = server.getAllConnectionInfo();
    ui->connection_list->setRowCount(0);
    foreach(QList<QString> const &row, data){
        int count = ui->connection_list->rowCount();
        ui->connection_list->insertRow(count);
        ui->connection_list->setItem(count, 0, new QTableWidgetItem(row[0]));
        ui->connection_list->setItem(count, 1, new QTableWidgetItem(row[1]));
        ui->connection_list->setItem(count, 2, new QTableWidgetItem(row[2]));
    }
    ui->connection_list->sortItems(0);
}

void NetworkView::networkSettingUpdate(){
    server.setAddress(ui->ip_edit->text());
    server.setPort(ui->port_edit->text().toInt());
    server.setPassword(ui->connect_password_edit->text());
    ui->server_start_btn->setEnabled(server.isReady());
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

void NetworkView::connectSignal(){
    connect(ui->ip_edit, SIGNAL(textChanged(QString)), this, SLOT(networkSettingUpdate()));
    connect(ui->port_edit, SIGNAL(textChanged(QString)), this, SLOT(networkSettingUpdate()));
    connect(ui->connect_password_edit, SIGNAL(textChanged(QString)), this, SLOT(networkSettingUpdate()));

    connect(ui->server_start_btn, SIGNAL(clicked(bool)), this, SLOT(startServer()));
    connect(ui->server_stop_btn, SIGNAL(clicked(bool)), this, SLOT(stopServer()));

    connect(&server, SIGNAL(connectionUpdate()), this, SLOT(serverConnectionUpdate()));
    connect(&server, SIGNAL(statusUpdate(QString)), this, SLOT(serverStatusUpdate(QString)));
}
