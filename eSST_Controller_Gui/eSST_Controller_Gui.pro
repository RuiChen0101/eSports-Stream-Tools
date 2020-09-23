QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eSST_Controller_Gui
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    file/file.cpp \
    file/file_manager.cpp \
    file/file_source.cpp \
    main.cpp \
    mainwindow.cpp \
    menubar.cpp \
    timer/chrono_down_timer.cpp \
    timer/countdown_timer.cpp \
    timer/date_time_timer.cpp \
    timer/timer.cpp \
    timer/timer_format_parser.cpp \
    utility/system_call.cpp \
    utility/timetick.cpp \
    view/timer_view.cpp

HEADERS += \
    file/file.h \
    file/file_manager.h \
    file/file_source.h \
    mainwindow.h \
    menubar.h \
    timer/chrono_down_timer.h \
    timer/countdown_timer.h \
    timer/date_time_timer.h \
    timer/timer.h \
    timer/timer_format_parser.h \
    utility/system_call.h \
    utility/timetick.h \
    view/timer_view.h

FORMS += \
    mainwindow.ui \
    view/timer_view.ui

DISTFILES += \
    eSST_Controller_Gui.pri
