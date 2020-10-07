QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "eSST Controller"
TEMPLATE = app

CONFIG += c++11

include(../eSST_Core/eSST_Core.pri)

RC_ICONS = resource/icon.ico

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    menubar.cpp \
    statusbar.cpp \
    view/network_view.cpp \
    view/score_board_view.cpp \
    view/timer_view.cpp

HEADERS += \
    mainwindow.h \
    menubar.h \
    statusbar.h \
    view/network_view.h \
    view/score_board_view.h \
    view/timer_view.h

FORMS += \
    mainwindow.ui \
    view/network_view.ui \
    view/score_board_view.ui \
    view/timer_view.ui

RESOURCES += \
    resource.qrc
