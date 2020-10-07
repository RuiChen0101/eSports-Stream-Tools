#include "network_view.h"
#include "ui_network_view.h"
#include "file/file_manager.h"
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
    deregisteOutputFile();
}

void NetworkView::configUpdate(){
    try {
        ui->message_display->setPlaceholderText(ShareConfig::inst()->read("messages").toString());
        team1Name.setString(ShareConfig::inst()->read("team1_name").toString());
        team1Point.setString(QString::number(ShareConfig::inst()->read("team1_point").toInt()));
        team1Round.setString(ShareConfig::inst()->read("team1_round").toString());
        team2Name.setString(ShareConfig::inst()->read("team2_name").toString());
        team2Point.setString(QString::number(ShareConfig::inst()->read("team2_point").toInt()));
        team2Round.setString(ShareConfig::inst()->read("team2_round").toString());

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

void NetworkView::scoreBoardUpdate(){
    ui->team1_name_edit->setText(team1Name.getString());
    ui->team1_point_display->display(team1Point.getString().toInt());
    ui->team1_round_point_display->setText(team1Round.getString());
    ui->team2_name_edit->setText(team2Name.getString());
    ui->team2_point_display->display(team2Point.getString().toInt());
    ui->team2_round_point_display->setText(team2Round.getString());
}

void NetworkView::fileOutputCheck(int status){
    if(status == Qt::Checked){
        registeOutputFile();
    }else if(status == Qt::Unchecked){
        deregisteOutputFile();
    }
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
            ui->file_output_check->setEnabled(true);
            fileOutputCheck(ui->file_output_check->checkState());
            break;
        default:
            disconnect(TimeTick::inst(), SIGNAL(timeUpdate()), this, SLOT(timeUpdate()));
            emit(SignalBus::inst()->systemMessageEvent("disconnected!!"));
            ui->connect_btn->setEnabled(client.isReady());
            ui->ip_edit->setEnabled(true);
            ui->name_edit->setEnabled(true);
            ui->port_edit->setEnabled(true);
            ui->connect_password_edit->setEnabled(true);
            ui->file_output_check->setEnabled(false);
            disconnected();
            break;
    }
}

void NetworkView::deregisteOutputFile(){
    FileManager::inst()->deregisteFile("DateTime.txt");
    FileManager::inst()->deregisteFile("Countdown.txt");
    FileManager::inst()->deregisteFile("ChronoDown.txt");
    FileManager::inst()->deregisteFile("team1Name.txt");
    FileManager::inst()->deregisteFile("team1Points.txt");
    FileManager::inst()->deregisteFile("team1RoundPoints.txt");
    FileManager::inst()->deregisteFile("team2Name.txt");
    FileManager::inst()->deregisteFile("team2Points.txt");
    FileManager::inst()->deregisteFile("team2RoundPoints.txt");
    ui->output_file_dir->setText("");
}

void NetworkView::registeOutputFile(){
    FileManager::inst()->registeTimerFile(&dateTime, "DateTime.txt");
    FileManager::inst()->registeTimerFile(&countdown, "Countdown.txt");
    FileManager::inst()->registeTimerFile(&chronoDown, "ChronoDown.txt");
    FileManager::inst()->registeScoreFile(&team1Name, "team1Name.txt");
    FileManager::inst()->registeScoreFile(&team1Point, "team1Points.txt");
    FileManager::inst()->registeScoreFile(&team1Round, "team1RoundPoints.txt");
    FileManager::inst()->registeScoreFile(&team2Name, "team2Name.txt");
    FileManager::inst()->registeScoreFile(&team2Point, "team2Points.txt");
    FileManager::inst()->registeScoreFile(&team2Round, "team2RoundPoints.txt");
    ui->output_file_dir->setText(FileManager::inst()->getRootDir().path());
}

void NetworkView::connectSignal(){
    connect(ui->ip_edit, SIGNAL(textChanged(QString)), this, SLOT(networkSettingUpdate()));
    connect(ui->port_edit, SIGNAL(textChanged(QString)), this, SLOT(networkSettingUpdate()));
    connect(ui->name_edit, SIGNAL(textChanged(QString)), this, SLOT(networkSettingUpdate()));
    connect(ui->connect_password_edit, SIGNAL(textChanged(QString)), this, SLOT(networkSettingUpdate()));

    connect(ui->connect_btn, SIGNAL(clicked(bool)), &client, SLOT(startConnect()));
    connect(ui->disconnect_btn, SIGNAL(clicked(bool)), &client, SLOT(stopConnect()));

    connect(ui->force_sync_btn, SIGNAL(clicked(bool)), &client, SLOT(forceSync()));
    connect(ui->file_output_check, SIGNAL(stateChanged(int)), this, SLOT(fileOutputCheck(int)));

    connect(&team1Name, SIGNAL(contentUpdate()), this, SLOT(scoreBoardUpdate()));
    connect(&team1Point, SIGNAL(contentUpdate()), this, SLOT(scoreBoardUpdate()));
    connect(&team1Round, SIGNAL(contentUpdate()), this, SLOT(scoreBoardUpdate()));
    connect(&team2Name, SIGNAL(contentUpdate()), this, SLOT(scoreBoardUpdate()));
    connect(&team2Point, SIGNAL(contentUpdate()), this, SLOT(scoreBoardUpdate()));
    connect(&team2Round, SIGNAL(contentUpdate()), this, SLOT(scoreBoardUpdate()));

    connect(ShareConfig::inst(), SIGNAL(configUpdate(QString)), this, SLOT(configUpdate()));

    connect(&client, SIGNAL(stateUpdate(QAbstractSocket::SocketState)), this, SLOT(socketStateUpdate(QAbstractSocket::SocketState)));
}

void NetworkView::loadConfig(){
    if(config.loadFile()){
        try{
            ui->ip_edit->setText(config.read("host_address").toString());
            ui->port_edit->setText(config.read("host_port").toString());
            ui->connect_password_edit->setText(config.read("host_password").toString());
            ui->name_edit->setText(config.read("receiver_name").toString());
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
    config.insert("receiver_name", ui->name_edit->text());
}
