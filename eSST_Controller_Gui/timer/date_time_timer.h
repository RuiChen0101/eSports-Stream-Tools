#ifndef DATETIMETIMER_H
#define DATETIMETIMER_H

#include "timer.h"

#include "file/file_source.h"

#include <QDateTime>

class DateTimeTimer : public Timer, public FileSource{
public:
    DateTimeTimer(QString const & = "");
    void setFormat(QString const &);
    QString getString() override;
    bool isOutputing() const override;
    void timeUpdate() override;
private:
    QString format;
    QDateTime currentTime;
};

#endif // DATETIMETIMER_H
