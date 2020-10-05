#ifndef SHARECONFIG_H
#define SHARECONFIG_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

class ShareConfig : public QObject{
    Q_OBJECT
friend class UtShareConfig;
public:
    static ShareConfig* inst();
    QString getConfigString();
    QJsonValue read(QString const &);
    void insert(QString const &, QJsonValue);
    void insert(QString const &);
    void commit();

signals:
    void configUpdate(QString);

private:
    ShareConfig(QObject * = nullptr);
    QJsonObject mergeObject(QJsonObject const &, QJsonObject const &);
    QJsonObject data;
    QJsonObject buffer;
};

#endif // SHARECONFIG_H
