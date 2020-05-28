QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

ConfigApp{
TARGET = eSST_Gui
TEMPLATE = app
}

ConfigTest{
TARGET = eSST_Gui_Lib
TEMPLATE = lib
CONFIG += staticlib
}

CONFIG += c++11

INCLUDEPATH += ./

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    view/timerview.cpp

HEADERS += \
    mainwindow.h \
    view/timerview.h

FORMS += \
    mainwindow.ui \
    view/timerview.ui

DISTFILES += \
    eSST_Gui.pri
