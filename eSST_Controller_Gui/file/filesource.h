#ifndef FILESOURCE_H
#define FILESOURCE_H

#include <QObject>
#include <QString>

class FileSource : public QObject{
    Q_OBJECT
public:
    explicit FileSource(QObject *parent = nullptr);
    virtual QString getString() = 0;
};

#endif // FILESOURCE_H
