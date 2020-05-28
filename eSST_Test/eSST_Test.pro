QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = eSST_Test
TEMPLATE = app
INCLUDEPATH += $$PWD/../eSST_Gui
DEPENDPATH += $$PWD/../eSST_Gui

include(./gtest/gtest.pri)
include(../eSST_Gui/eSST_Gui.pri)

SOURCES += main.cpp

HEADERS  += \
    test/ut_test.h
