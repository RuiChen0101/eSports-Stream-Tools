#ifndef POINT_H
#define POINT_H

#include "file/file_source.h"

class Point : public FileSource{
public:
    Point();
    void reset();
    void addPoint(qint8);
    qint8 getPoint() const;
    QString getString() override;
    bool isOutputing() const override;
private:
    qint8 points;
};

#endif // SCORE_H
