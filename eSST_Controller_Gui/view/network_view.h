#ifndef NETWORK_VIEW_H
#define NETWORK_VIEW_H

#include <QWidget>

namespace Ui {
class NetworkView;
}

class NetworkView : public QWidget{
    Q_OBJECT

public:
    NetworkView(QWidget *parent = nullptr);
    ~NetworkView();

private:
    Ui::NetworkView *ui;
};

#endif // NETWORK_VIEW_H
