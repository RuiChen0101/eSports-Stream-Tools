#define TEST
#include <QtTest>

#include "testexec.h"

#include "testsetup.h"

int main(int argc, char *argv[]){
    int status = 0;
    TestSetUp test;
    status |= QTest::qExec(&test, argc, argv);
    return status | TestExec::runAllTest(argc, argv);
}
