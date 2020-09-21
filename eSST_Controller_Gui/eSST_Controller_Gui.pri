QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/file/filesource.cpp \
    $$PWD/mainwindow.cpp \
    $$PWD/timer/chronodowntimer.cpp \
    $$PWD/timer/countdowntimer.cpp \
    $$PWD/timer/datetimetimer.cpp \
    $$PWD/timer/timerformatparser.cpp \
    $$PWD/timer/timer.cpp \
    $$PWD/utility/timetick.cpp \
    $$PWD/view/timerview.cpp

HEADERS += \
    $$PWD/file/filesource.h \
    $$PWD/mainwindow.h \
    $$PWD/timer/chronodowntimer.h \
    $$PWD/timer/countdowntimer.h \
    $$PWD/timer/datetimetimer.h \
    $$PWD/timer/timerformatparser.h \
    $$PWD/timer/timer.h \
    $$PWD/utility/timetick.h \
    $$PWD/view/timerview.h

FORMS += \
    $$PWD/mainwindow.ui \
    $$PWD/view/timerview.ui
