#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QObject>
#include <QStatusBar>

class StatusBar : public QObject{
    Q_OBJECT
public:
    StatusBar(QStatusBar*, QObject *parent = nullptr);
public slots:
    void systemMessageEvent(QString);
private:
    QStatusBar *statusBar;
};

#endif // STATUSBAR_H
