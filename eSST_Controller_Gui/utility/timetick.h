#ifndef TIMETICK_H
#define TIMETICK_H

#include <QtCore>
#include <QObject>

class TimeTick : public QObject{
    Q_OBJECT

public:
    static TimeTick* inst();
    ~TimeTick();
signals:
    void timeUpdate();
private:
    explicit TimeTick(QObject *parent = nullptr);
    QTimer *timer;
};

#endif // TIMETICK_H
