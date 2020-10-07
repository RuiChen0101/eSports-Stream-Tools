QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "eSST Receiver"
TEMPLATE = app

CONFIG += c++11

include(../eSST_Core/eSST_Core.pri)

RC_ICONS = resource/icon.ico

SOURCES += \
    main.cpp \
    menubar.cpp \
    statusbar.cpp \
    mainwindow.cpp \
    view/network_view.cpp

HEADERS += \
    menubar.h \
    statusbar.h \
    mainwindow.h \
    view/network_view.h

FORMS += \
    mainwindow.ui \
    view/network_view.ui
