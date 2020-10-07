#ifndef NETWORK_VIEW_H
#define NETWORK_VIEW_H

#include "timer/date_time_timer.h"
#include "timer/countdown_timer.h"
#include "timer/chrono_down_timer.h"
#include "network/tcp_client.h"
#include "file/config_file.h"
#include "file/file_source.h"

#include <QWidget>

namespace Ui {
class NetworkView;
}

class NetworkView : public QWidget{
    Q_OBJECT

public:
    NetworkView(QWidget *parent = nullptr);
    ~NetworkView();

private slots:
    void timeUpdate();
    void disconnected();
    void configUpdate();
    void scoreBoardUpdate();
    void fileOutputCheck(int);
    void networkSettingUpdate();
    void socketStateUpdate(QAbstractSocket::SocketState);

private:
    void deregisteOutputFile();
    void registeOutputFile();
    void connectSignal();
    void loadConfig();
    void saveConfig();
    Ui::NetworkView *ui;
    TcpClient client;
    ConfigFile config;
    DateTimeTimer dateTime;
    CountDownTimer countdown;
    ChronoDownTimer chronoDown;
    FileSource team1Name, team1Point, team1Round;
    FileSource team2Name, team2Point, team2Round;
};

#endif // NETWORK_VIEW_H
