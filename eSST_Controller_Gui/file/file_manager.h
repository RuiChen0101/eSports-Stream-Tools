#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "file.h"
#include "file_source.h"

#include <QDir>
#include <QMap>
#include <QList>
#include <QObject>

class FileManager : public QObject{
    Q_OBJECT
friend class UtFileManager;
public:
    static FileManager* inst();
    ~FileManager();
    QDir getTextFileDir() const;
    QDir getConfigFileDir() const;
    QString registeTextFile(FileSource*, QString const &);
    void deregisteTextFile(QString const &);
private:
    FileManager(QObject *parent = nullptr);
    void prepareFolder(QDir const &);
    QDir textFileDir;
    QDir confileFileDir;
    QMap<QString, File*> files;
};

#endif // FILEMANAGER_H
