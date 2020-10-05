#include "network_view.h"
#include "ui_network_view.h"
#include "network/share_config.h"
#include "utility/timetick.h"
#include "utility/signal_bus.h"

NetworkView::NetworkView(QWidget *parent) :
    QWidget(parent), ui(new Ui::NetworkView), config("NetworkViewConfig.json"){
    ui->setupUi(this);
    loadConfig();
    connectSignal();
    networkSettingUpdate();
}

NetworkView::~NetworkView(){
    saveConfig();
    delete ui;
}

void NetworkView::timeUpdate(){
    dateTime.timeUpdate();
    countdown.timeUpdate();
    chronoDown.timeUpdate();
    ui->datetime_live_output->setText(dateTime.getString());
    ui->countdown_live_output->setText(countdown.getString());
    ui->chronodown_live_output->setText(chronoDown.getString());
}

void NetworkView::disconnected(){
    ui->message_display->setPlaceholderText("");
    ui->team1_name_edit->clear();
    ui->team1_point_display->display(0);
    ui->team1_round_point_display->clear();
    ui->team2_name_edit->clear();
    ui->team2_point_display->display(0);
    ui->team2_round_point_display->clear();
    ui->datetime_live_output->clear();
    ui->countdown_live_output->clear();
    ui->chronodown_live_output->clear();
}

void NetworkView::configUpdate(){
    try {
        ui->message_display->setPlaceholderText(ShareConfig::inst()->read("messages").toString());
        ui->team1_name_edit->setText(ShareConfig::inst()->read("team1_name").toString());
        ui->team1_point_display->display(ShareConfig::inst()->read("team1_point").toInt());
        ui->team1_round_point_display->setText(ShareConfig::inst()->read("team1_round").toString());
        ui->team2_name_edit->setText(ShareConfig::inst()->read("team2_name").toString());
        ui->team2_point_display->display(ShareConfig::inst()->read("team2_point").toInt());
        ui->team2_round_point_display->setText(ShareConfig::inst()->read("team2_round").toString());

        dateTime.setFormat(ShareConfig::inst()->read("date_time_format").toString());

        countdown.setFormat(ShareConfig::inst()->read("countdown_format").toString());
        countdown.setTimeoutMsg(ShareConfig::inst()->read("countdown_timeout_msg").toString());
        countdown.setDoubleDigit(ShareConfig::inst()->read("countdown_double_digit").toBool());
        countdown.setStatus(CountDownTimer::Status(ShareConfig::inst()->read("countdown_status").toInt()));
        QJsonArray countdownTarget = ShareConfig::inst()->read("countdown_target").toArray();
        QDate countdownDate(countdownTarget[0].toInt(), countdownTarget[1].toInt(), countdownTarget[2].toInt());
        QTime countdownTime(countdownTarget[3].toInt(), countdownTarget[4].toInt(), countdownTarget[5].toInt());
        countdown.setTarget(QDateTime(countdownDate, countdownTime));

        chronoDown.setFormat(ShareConfig::inst()->read("chrono_down_format").toString());
        chronoDown.setTimeoutMsg(ShareConfig::inst()->read("chrono_down_timeout_msg").toString());
        chronoDown.setDoubleDigit(ShareConfig::inst()->read("chrono_down_double_digit").toBool());
        chronoDown.setStatus(ChronoDownTimer::Status(ShareConfig::inst()->read("chrono_down_status").toInt()));
        QJsonArray chronoDownTarget = ShareConfig::inst()->read("chrono_down_target").toArray();
        chronoDown.setTarget(QTime(chronoDownTarget[0].toInt(), chronoDownTarget[1].toInt(), chronoDownTarget[2].toInt()));
    }catch (std::runtime_error &e) {}
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
            connect(TimeTick::inst(), SIGNAL(timeUpdate()), this, SLOT(timeUpdate()));
            break;
        default:
            disconnect(TimeTick::inst(), SIGNAL(timeUpdate()), this, SLOT(timeUpdate()));
            emit(SignalBus::inst()->systemMessageEvent("disconnected!!"));
            ui->connect_btn->setEnabled(client.isReady());
            ui->ip_edit->setEnabled(true);
            ui->name_edit->setEnabled(true);
            ui->port_edit->setEnabled(true);
            ui->connect_password_edit->setEnabled(true);
            disconnected();
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

    connect(ui->force_sync_btn, SIGNAL(clicked(bool)), &client, SLOT(forceSync()));

    connect(ShareConfig::inst(), SIGNAL(configUpdate(QString)), this, SLOT(configUpdate()));

    connect(&client, SIGNAL(stateUpdate(QAbstractSocket::SocketState)), this, SLOT(socketStateUpdate(QAbstractSocket::SocketState)));
}

void NetworkView::loadConfig(){
    if(config.loadFile()){
        try{
            ui->ip_edit->setText(config.read("host_address").toString());
            ui->port_edit->setText(config.read("host_port").toString());
            ui->connect_password_edit->setText(config.read("host_password").toString());
            ui->name_edit->setText(config.read("reciver_name").toString());
        }catch(std::runtime_error &e){
            emit(SignalBus::inst()->systemMessageEvent("load config fail"));
        }
    }else{
        emit(SignalBus::inst()->systemMessageEvent("load config fail"));
    }
}

void NetworkView::saveConfig(){
    config.insert("host_address", ui->ip_edit->text());
    config.insert("host_port", ui->port_edit->text());
    config.insert("host_password", ui->connect_password_edit->text());
    config.insert("reciver_name", ui->name_edit->text());
}
