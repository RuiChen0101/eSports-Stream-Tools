#include "share_config.h"

ShareConfig* ShareConfig::inst(){
    static ShareConfig Inst;
    return &Inst;
}

ShareConfig::ShareConfig(QObject *parent):
    QObject(parent){
    buffer = QJsonObject();
}

QString ShareConfig::getConfigString(){
    QJsonDocument doc;
    doc.setObject(data);
    return doc.toJson(QJsonDocument::Compact);
}

QJsonValue ShareConfig::read(QString const &key){
    if(data.contains(key)){
        return data.value(key);
    }else{
        throw std::runtime_error("ConfigFile: key not found");
    }
}

void ShareConfig::insert(QString const &key, QJsonValue value){
    buffer.insert(key, value);
}

void ShareConfig::insert(QString const &json){
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if(doc.isObject()){
        QJsonObject obj = doc.object();
        buffer = mergeObject(buffer, obj);
    }
}

void ShareConfig::commit(){
    data = mergeObject(data, buffer);
    QJsonDocument doc;
    doc.setObject(buffer);
    emit(configUpdate(doc.toJson(QJsonDocument::Compact)));
    buffer = QJsonObject();
}

QJsonObject ShareConfig::mergeObject(QJsonObject const &first, QJsonObject const &second){
    QJsonObject result = first;
    foreach(QString const &key, second.keys()){
        result[key] = second[key];
    }
    return result;
}
