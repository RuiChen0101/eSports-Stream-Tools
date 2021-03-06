#include "file_manager.h"

QString FileManager::folder = "/eSST";

void FileManager::changeRootFolder(QString const &folder){
    FileManager::folder = folder;
}

FileManager* FileManager::inst(){
    static FileManager Inst;
    return &Inst;
}

FileManager::FileManager(QObject *parent):
    QObject(parent){
    rootDir.setPath(QDir::homePath() + FileManager::folder);
    timerFileDir.setPath(rootDir.path() + "/TimerFiles");
    scoreFileDir.setPath(rootDir.path() + "/ScoreFiles");
    configFileDir.setPath(rootDir.path() + "/ConfigFiles");
    prepareFolder(rootDir);
    prepareFolder(timerFileDir);
    prepareFolder(scoreFileDir);
    prepareFolder(configFileDir);
}

FileManager::~FileManager(){
    QList<File*> values = files.values();
    foreach(File *value, values) {
        delete value;
    }
    files.clear();
}

QDir FileManager::getRootDir() const{
    prepareFolder(rootDir);
    return rootDir;
}

QDir FileManager::getTimerFileDir() const{
    prepareFolder(timerFileDir);
    return timerFileDir;
}

QDir FileManager::getScoreFileDir() const{
    prepareFolder(scoreFileDir);
    return scoreFileDir;
}

QDir FileManager::getConfigFileDir() const{
    prepareFolder(configFileDir);
    return configFileDir;
}

QString FileManager::getFilePathByName(QString const &fileName){
    if(files.contains(fileName)){
        return files[fileName]->getFilePath();
    }else{
        return "";
    }
}

QString FileManager::registeTimerFile(FileSource *source, QString const &fileName){
    return registeFile(source, timerFileDir, fileName);
}

QString FileManager::registeScoreFile(FileSource *source, QString const &fileName){
    return registeFile(source, scoreFileDir, fileName);
}

void FileManager::deregisteFile(QString const &fileName){
    if(files.contains(fileName)){
        delete files[fileName];
        files.remove(fileName);
    }
}

QString FileManager::registeFile(FileSource *source, QDir const &dir, QString const &fileName){
    if(files.contains(fileName)){
        files[fileName]->setFileSource(source);
        return files[fileName]->getFilePath();
    }else{
        QString filePath = dir.filePath(fileName);
        files.insert(fileName, new File(source, filePath));
        return filePath;
    }
}

void FileManager::prepareFolder(QDir const &folder) const{
    if(!folder.exists()){
        folder.mkpath(folder.path());
    }
}
