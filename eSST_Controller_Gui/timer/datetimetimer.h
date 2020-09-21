#ifndef DATETIMETIMER_H
#define DATETIMETIMER_H

#include "timer.h"

#include <QDateTime>

class DateTimeTimer : public Timer{
public:
    DateTimeTimer(QString const & = "");
    void setFormat(QString const &) override;
    QString getString() override;
    void timeUpdate() override;
private:
    QString format;
    QDateTime currentTime;
};

#endif // DATETIMETIMER_H
