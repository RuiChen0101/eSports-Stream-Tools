#include <gtest/gtest.h>
#include <QApplication>
#include "test/ut_test.h"

int main(int argc, char *argv[]){
    QApplication a(argc,argv);
    testing::InitGoogleTest(&argc,argv);

    return RUN_ALL_TESTS();
}
