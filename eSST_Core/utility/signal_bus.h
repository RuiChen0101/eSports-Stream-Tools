#ifndef SIGNALBUS_H
#define SIGNALBUS_H

#include <QObject>

class SignalBus : public QObject{
    Q_OBJECT
public:
    static SignalBus* inst();
signals:
    void systemMessageEvent(QString);
private:
    SignalBus(QObject *parent = nullptr);

};

#endif // SIGNALBUS_H
