QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eSST_Controller_Gui
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    file/filesource.cpp \
    main.cpp \
    mainwindow.cpp \
    timer/chronodowntimer.cpp \
    timer/countdowntimer.cpp \
    timer/datetimetimer.cpp \
    timer/timer.cpp \
    timer/timerformatparser.cpp \
    utility/timetick.cpp \
    view/timerview.cpp

HEADERS += \
    file/filesource.h \
    mainwindow.h \
    timer/chronodowntimer.h \
    timer/countdowntimer.h \
    timer/datetimetimer.h \
    timer/timer.h \
    timer/timerformatparser.h \
    utility/timetick.h \
    view/timerview.h

FORMS += \
    mainwindow.ui \
    view/timerview.ui

DISTFILES += \
    eSST_Controller_Gui.pri
