QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

include(../eSST_Controller_Gui/eSST_Controller_Gui.pri)

SOURCES +=  \
    main.cpp \

HEADERS += \
    ut_timer/ut_chronodowntimer.h \
    ut_timer/ut_timerformatparser.h \
    testexec.h
