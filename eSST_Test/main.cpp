#include <QtTest>
#include <QApplication>

#include "testexec.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    return TestExec::runAllTest(argc, argv);
}
