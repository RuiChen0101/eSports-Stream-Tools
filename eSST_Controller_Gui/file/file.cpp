#include "file.h"

File::File(FileSource *source, QString const &path):
    QObject(nullptr), file(path), path(path), source(source){
    if(file.open(QIODevice::WriteOnly | QFile::Truncate)){
        if(source->isOutputing()){
            file.write(source->getString().toUtf8());
        }
        file.close();
    }else{
        throw std::runtime_error("file " + path.toUtf8() + " open fail");
    }
    connect(source, SIGNAL(contentUpdate()), this, SLOT(fileUpdate()));
}

File::~File(){
    file.resize(0);
}

void File::fileUpdate(){
    if(source->isOutputing() && file.open(QIODevice::WriteOnly | QFile::Truncate)){
        file.write(source->getString().toUtf8());
        file.close();
    }else{
        file.resize(0);
    }
}

QString File::getFilePath() const{
    return path;
}

void File::setFileSource(FileSource *newSource){
    disconnect(source, SIGNAL(contentUpdate()), this, SLOT(fileUpdate()));
    this->source = newSource;
    connect(source, SIGNAL(contentUpdate()), this, SLOT(fileUpdate()));
    fileUpdate();
}

QString File::readAll(){
    if(!file.open(QIODevice::ReadOnly)){
        throw std::runtime_error("file " + path.toUtf8() + " open fail");
    }
    QTextStream inStream(&file);
    QString result = inStream.readAll();
    file.close();
    return result;
}
