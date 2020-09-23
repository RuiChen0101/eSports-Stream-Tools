#ifndef FILESOURCE_H
#define FILESOURCE_H

#include <QObject>
#include <QString>

class FileSource : public QObject{
    Q_OBJECT
public:
    FileSource(QObject *parent = nullptr);
    virtual QString getString() = 0;
    virtual bool isOutputing() const = 0;
signals:
    void contentUpdate();
};

#endif // FILESOURCE_H
