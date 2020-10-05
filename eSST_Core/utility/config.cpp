#include "config.h"
#include "file/file_manager.h"
#include <QDebug>

const QString Config::fileName = "config.json";

Config* Config::inst(){
    static Config Inst;
    return &Inst;
}

Config::Config(QObject *parent):
    QObject(parent){
    QString path = FileManager::inst()->getConfigFileDir().filePath(Config::fileName);
    file.setFileName(path);
    buffer = QJsonObject();
}

Config::~Config(){
    saveFile();
}

bool Config::isLoaded(){
    return !data.isEmpty();
}

bool Config::loadFile(){
    if(file.exists() && file.open(QIODevice::ReadOnly)){
        QString dataStr = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(dataStr.toUtf8());
        if(doc.isObject()){
            data = doc.object();
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

void Config::saveFile(){
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QJsonDocument doc;
        doc.setObject(data);
        file.write(doc.toJson(QJsonDocument::Compact));
        file.close();
    }
}

QString Config::getConfigString(){
    QJsonDocument doc;
    doc.setObject(data);
    return doc.toJson(QJsonDocument::Compact);
}

QJsonValue Config::read(QString const &key){
    if(data.contains(key)){
        return data.value(key);
    }else{
        throw std::runtime_error("ConfigFile: key not found");
    }
}

void Config::insert(QString const &key, QJsonValue value){
    buffer.insert(key, value);
}

void Config::insert(QString const &json){
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if(doc.isObject()){
        QJsonObject obj = doc.object();
        buffer = mergeObject(buffer, obj);
    }
}

void Config::commit(){
    data = mergeObject(data, buffer);
    QJsonDocument doc;
    doc.setObject(buffer);
    emit(configUpdate(doc.toJson(QJsonDocument::Compact)));
    buffer = QJsonObject();
}

QJsonObject Config::mergeObject(QJsonObject const &first, QJsonObject const &second){
    QJsonObject result = first;
    foreach(QString const &key, second.keys()){
        result[key] = second[key];
    }
    return result;
}
