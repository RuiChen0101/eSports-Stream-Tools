#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include "file/file.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

class ConfigFile{
friend class UtConfigFile;

public:
    ConfigFile(QString const &);
    ~ConfigFile();
    bool loadFile();
    void saveFile();
    QJsonValue read(QString const &);
    void insert(QString const &, QJsonValue);
private:
    QFile file;
    QString path;
    QString fileName;
    QJsonObject data;
};

#endif // CONFIGFILE_H
