#include "file_source.h"

FileSource::FileSource(QObject *parent):
    QObject(parent){

}

QString FileSource::getString(){
    return string;
}

bool FileSource::isOutputing() const{
    return true;
}

void FileSource::setString(QString const &string){
    this->string = string;
    emit(contentUpdate());
}
