#ifndef TIMERFORMATPARSER_H
#define TIMERFORMATPARSER_H

#include <QChar>
#include <QObject>
#include <QString>

struct StTimeUnit{
    quint8 sec;
    quint8 min;
    quint8 hour;
    quint8 day;
    void fromSecond(qint64);
};

class TimerFormatParser{
friend class UtTimerFormatParser;

public:
    TimerFormatParser();
    void setFormat(QString const &);
    void setSecond(qint64 const &);
    void setDoubleDigit(bool);
    QString getString();

private:
    QString numberToString(quint8);
    bool useDoubleDigit;
    QString format;
    StTimeUnit timeUnit;
};

#endif // TIMERFORMATPARSER_H
