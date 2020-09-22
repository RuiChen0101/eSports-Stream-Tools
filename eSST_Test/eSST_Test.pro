QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

include(../eSST_Controller_Gui/eSST_Controller_Gui.pri)

SOURCES +=  \
    main.cpp



HEADERS += \
    testexec.h \
    testsetup.h \
    ut_timer/ut_countdowntimer.h \
    ut_timer/ut_timerformatparser.h \
    ut_timer/ut_chronodowntimer.h
