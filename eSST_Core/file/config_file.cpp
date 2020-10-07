#include "config_file.h"
#include "file_manager.h"

ConfigFile::ConfigFile(QString const &fileName, QObject *parent):
    QObject(parent){
    QString path = FileManager::inst()->getConfigFileDir().filePath(fileName);
    file.setFileName(path);
}

ConfigFile::~ConfigFile(){
    saveFile();
}

bool ConfigFile::loadFile(){
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

void ConfigFile::saveFile(){
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QJsonDocument doc;
        doc.setObject(data);
        file.write(doc.toJson(QJsonDocument::Compact));
        file.close();
    }
}

QJsonValue ConfigFile::read(QString const &key){
    if(data.contains(key)){
        return data.value(key);
    }else{
        throw std::runtime_error("ConfigFile: key not found");
    }
}

void ConfigFile::insert(QString const &key, QJsonValue value){
    data.insert(key, value);
}
