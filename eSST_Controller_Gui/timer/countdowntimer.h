#ifndef COUNTDOWNTIMER_H
#define COUNTDOWNTIMER_H

#include "timer.h"
#include "timerformatparser.h"

#include <QDateTime>
#include <QTimeZone>

class CountDownTimer : public Timer{
public:
    enum Status{
        START,
        STOP
    };
    CountDownTimer();
    QString getString() override;
    void setFormat(QString const &) override;
    void setTarget(QDateTime const &);
    void setStatus(Status);
    void setTimeoutMsg(QString const &);
    void setDoubleDigit(bool);
    void timeUpdate() override;
private:
    Status status = STOP;
    QString timeoutMsg;
    qint64 remainSec;
    TimerFormatParser parser;
};

#endif // COUNTDOWNTIMER_H
