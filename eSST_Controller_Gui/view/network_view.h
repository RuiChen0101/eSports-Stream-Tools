#ifndef NETWORK_VIEW_H
#define NETWORK_VIEW_H

#include "network/tcp_server.h"

#include <QList>
#include <QString>
#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class NetworkView;
}

class NetworkView : public QWidget{
    Q_OBJECT

public:
    NetworkView(QWidget *parent = nullptr);
    ~NetworkView();

private slots:
    void serverLogUpdate(QString);
    void serverConnectionUpdate();
    void networkSettingUpdate();
    void kickConnection();
    void startServer();
    void stopServer();
    void clearLog();

private:
    void connectSignal();
    Ui::NetworkView *ui;
    TcpServer server;
};

#endif // NETWORK_VIEW_H
