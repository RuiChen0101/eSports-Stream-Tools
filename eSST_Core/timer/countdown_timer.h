#ifndef COUNTDOWNTIMER_H
#define COUNTDOWNTIMER_H

#include "timer.h"
#include "timer_format_parser.h"

#include "file/file_source.h"

#include <QDateTime>
#include <QTimeZone>

class CountDownTimer : public Timer, public FileSource{
friend class UtCountDownTimer;

public:
    enum Status{
        START,
        STOP
    };
    CountDownTimer();
    QString getString() override;
    bool isOutputing() const override;
    void setFormat(QString const &);
    void setTarget(QDateTime const &);
    void setStatus(Status);
    void setTimeoutMsg(QString const &);
    void setDoubleDigit(bool);
    void timeUpdate() override;

private:
    Status status = STOP;
    qint64 remainSec;
    QString timeoutMsg;
    TimerFormatParser parser;
};

#endif // COUNTDOWNTIMER_H
