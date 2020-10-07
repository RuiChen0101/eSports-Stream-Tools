#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QFile>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

class ConfigFile : public QObject{
    Q_OBJECT
friend class UtConfigFile;
public:
    ConfigFile(QString const &, QObject * = nullptr);
    ~ConfigFile();
    bool loadFile();
    void saveFile();
    QJsonValue read(QString const &);
    void insert(QString const &, QJsonValue);

private:
    QFile file;
    QJsonObject data;
};

#endif // CONFIGFILE_H
