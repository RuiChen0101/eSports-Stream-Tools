#ifndef FAKE_FILE_SOURCE_H
#define FAKE_FILE_SOURCE_H

#include "file/file_source.h"

#include <QString>

class FakeFileSource : public FileSource{
public:
    FakeFileSource();
    QString getString() override;
    bool isOutputing() const override;
    void setString(QString const &);
    void setOutputing(bool);
private:
    QString string;
    bool outputing;
};

#endif // FAKE_FILE_SOURCE_H
