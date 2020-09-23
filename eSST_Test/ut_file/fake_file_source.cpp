#include "fake_file_source.h"

FakeFileSource::FakeFileSource():
    string(""), outputing(false){}

QString FakeFileSource::getString(){
    return string;
}

bool FakeFileSource::isOutputing() const{
    return outputing;
}

void FakeFileSource::setString(QString const &string){
    this->string = string;
    contentUpdate();
}

void FakeFileSource::setOutputing(bool flag){
    this->outputing = flag;
}
