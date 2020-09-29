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
    QDir getTimerFileDir() const;
    QDir getScoreFileDir() const;
    QDir getConfigFileDir() const;
    QString getFilePathByName(QString const &);
    QString registeTimerFile(FileSource*, QString const &);
    QString registeScoreFile(FileSource*, QString const &);
    void deregisteFile(QString const &);
private:
    FileManager(QObject *parent = nullptr);
    QString registeFile(FileSource*, QDir const &, QString const &);
    void prepareFolder(QDir const &);
    QDir rootDir;
    QDir timerFileDir;
    QDir scoreFileDir;
    QDir confileFileDir;
    QMap<QString, File*> files;
};

#endif // FILEMANAGER_H
