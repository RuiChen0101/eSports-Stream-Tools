QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

include(../eSST_Controller_Gui/eSST_Controller_Gui.pri)

SOURCES +=  \
    main.cpp \
    ut_file/fake_file_source.cpp



HEADERS += \
    testexec.h \
    testsetup.h \
    ut_file/fake_file_source.h \
    ut_file/ut_file.h \
    ut_file/ut_file_manager.h \
    ut_timer/ut_countdowntimer.h \
    ut_timer/ut_datetimetimer.h \
    ut_timer/ut_timerformatparser.h \
    ut_timer/ut_chronodowntimer.h
