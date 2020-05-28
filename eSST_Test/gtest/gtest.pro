TARGET = GoogleTest
TEMPLATE = lib

CONFIG += staticlib exceptions
CONFIG -= debug_and_release
CONFIG += c++11

INCLUDEPATH += googletest/ \
    googlemock/ \
    googletest/include \
    googlemock/include \

SOURCES += \
    googletest/src/gtest-all.cc \
    googlemock/src/gmock-all.cc

DISTFILES += \
    gtest.pri
