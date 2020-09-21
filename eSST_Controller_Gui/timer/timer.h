#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QString>

class Timer : public QObject{
    Q_OBJECT
public:
    explicit Timer(QObject *parent = nullptr);
    virtual ~Timer();
    virtual void setFormat(QString const &) = 0;
    virtual QString getString() = 0;
    virtual void timeUpdate() = 0;
};

#endif // TIMER_H
