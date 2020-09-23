#ifndef FILE_H
#define FILE_H

#include "file_source.h"

#include <QFile>
#include <QObject>
#include <QTextStream>

class File : public QObject{
    Q_OBJECT
friend class UtFile;
public:
    File(FileSource*, QString const &);
    ~File();
    QString getFilePath() const;
    void setFileSource(FileSource*);
    QString readAll();
public slots:
    void fileUpdate();
private:
    QFile file;
    QString path;
    FileSource *source;
};

#endif // FILE_H
