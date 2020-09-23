#ifndef CHRONODOWNTIMER_H
#define CHRONODOWNTIMER_H

#include "timer.h"
#include "timer_format_parser.h"

#include "file/file_source.h"

#include <QTime>
#include <QDebug>

class ChronoDownTimer : public Timer, public FileSource{
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
    bool isOutputing() const override;
    void setFormat(QString const &);
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
