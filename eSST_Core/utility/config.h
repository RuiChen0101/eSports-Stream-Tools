#ifndef CONFIG_H
#define CONFIG_H

#include <QFile>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

class Config : public QObject{
    Q_OBJECT
friend class UtConfig;
public:
    static Config* inst();
    ~Config();
    bool isLoaded();
    bool loadFile();
    void saveFile();
    QString getConfigString();
    QJsonValue read(QString const &);
    void insert(QString const &, QJsonValue);
    void insert(QString const &);
    void commit();

signals:
    void configUpdate(QString);

private:
    Config(QObject * = nullptr);
    QJsonObject mergeObject(QJsonObject const &, QJsonObject const &);
    const static QString fileName;
    QFile file;
    QJsonObject data;
    QJsonObject buffer;
};

#endif // CONFIG_H
