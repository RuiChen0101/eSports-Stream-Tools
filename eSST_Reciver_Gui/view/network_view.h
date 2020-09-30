#ifndef NETWORK_VIEW_H
#define NETWORK_VIEW_H

#include "network/tcp_client.h"

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
    void networkSettingUpdate();
    void socketStateUpdate(QAbstractSocket::SocketState);

private:
    void connectSignal();
    Ui::NetworkView *ui;
    TcpClient client;

};

#endif // NETWORK_VIEW_H
