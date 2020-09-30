#define TEST
#include <QtTest>

#include "testexec.h"

#include "testinit.h"
#include "testcleanup.h"

int main(int argc, char *argv[]){
    int status = 0;
    TestInit testInit;
    status |= QTest::qExec(&testInit, argc, argv);
    status |= TestExec::runAllTest(argc, argv);
    TestCleanup testCleanup;
    return status | QTest::qExec(&testCleanup, argc, argv);
}
