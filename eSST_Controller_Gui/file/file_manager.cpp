#include "file_manager.h"

FileManager* FileManager::inst(){
    static FileManager Inst;
    return &Inst;
}

FileManager::~FileManager(){
    QList<File*> values = files.values();
    foreach(File *value, values) {
        delete value;
    }
    files.clear();
}

FileManager::FileManager(QObject *parent):
    QObject(parent){
    textFileDir.setPath(QDir::currentPath() + "/TextFiles");
    confileFileDir.setPath(QDir::currentPath() + "/ConfigFiles");
    prepareFolder(textFileDir);
    prepareFolder(confileFileDir);
}

QDir FileManager::getTextFileDir() const{
    return textFileDir;
}

QDir FileManager::getConfigFileDir() const{
    return confileFileDir;
}

QString FileManager::registeTextFile(FileSource *source, QString const &fileName){
    if(files.contains(fileName)){
        files[fileName]->setFileSource(source);
        return files[fileName]->getFilePath();
    }else{
        QString filePath = textFileDir.filePath(fileName);
        files.insert(fileName, new File(source, filePath));
        return filePath;
    }
}

void FileManager::deregisteTextFile(QString  const &fileName){
    if(files.contains(fileName)){
        delete files[fileName];
        files.remove(fileName);
    }
}

void FileManager::prepareFolder(QDir const &folder){
    if(!folder.exists()){
        folder.mkdir(".");
    }
}
