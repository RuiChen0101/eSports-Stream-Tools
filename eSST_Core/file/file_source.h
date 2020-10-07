#ifndef FILESOURCE_H
#define FILESOURCE_H

#include <QObject>
#include <QString>

class FileSource : public QObject{
    Q_OBJECT
public:
    FileSource(QObject *parent = nullptr);
    virtual QString getString();
    virtual bool isOutputing() const;
    void setString(QString const &);
signals:
    void contentUpdate();
private:
    QString string;
};

#endif // FILESOURCE_H
