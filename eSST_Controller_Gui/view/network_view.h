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
    void serverStatusUpdate(QString);
    void serverConnectionUpdate();
    void networkSettingUpdate();
    void startServer();
    void stopServer();

private:
    void connectSignal();
    Ui::NetworkView *ui;
    TcpServer server;
};

#endif // NETWORK_VIEW_H