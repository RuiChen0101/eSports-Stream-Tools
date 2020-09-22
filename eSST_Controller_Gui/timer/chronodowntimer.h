#ifndef CHRONODOWNTIMER_H
#define CHRONODOWNTIMER_H

#include "timer.h"
#include "timerformatparser.h"

#include <QTime>
#include <QDebug>

class ChronoDownTimer : public Timer{
friend class UtChronoDownTimer;

public:
    enum Status{
        START,
        PAUSE,
        STOP,
        RESUME
    };
    ChronoDownTimer();
    QString getString() override;
    void setFormat(QString const &) override;
    void setTarget(QTime const &);
    void setStatus(Status);
    void setTimeoutMsg(QString const &);
    void setDoubleDigit(bool);
    void timeUpdate() override;
private:
    Status status = STOP;
    QTime target;
    QString timeoutMsg;
    qint64 remainSec;
    TimerFormatParser parser;
};

#endif // CHRONODOWNTIMER_H
