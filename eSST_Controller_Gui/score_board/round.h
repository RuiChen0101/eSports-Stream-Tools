#ifndef ROUND_H
#define ROUND_H

#include <file/file_source.h>

class Round : public FileSource{
friend class UtRound;

public:
    Round();
    static void setUseDigit(bool);
    static void setBestOf(qint8);
    static void setFormat(QString const &);
    void addPoint(qint8);
    QString getString() override;
    bool isOutputing() const override;
    void setInvert(bool);
    void settingUpdate();
    void reset();
private:
    QString parseFormat();
    static qint8 bestOf;
    static QString format;
    static bool useDigit;
    qint8 points;
    bool isInvert;
};

#endif // ROUND_H
