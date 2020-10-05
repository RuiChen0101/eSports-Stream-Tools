QT += testlib
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

CONFIG += c++11

include(../eSST_Core/eSST_Core.pri)

SOURCES +=  \
    main.cpp \
    ut_file/fake_file_source.cpp

HEADERS += \
    testcleanup.h \
    testexec.h \
    testinit.h \
    ut_file/fake_file_source.h \
    ut_file/ut_config_file.h \
    ut_file/ut_file.h \
    ut_file/ut_file_manager.h \
    ut_file/ut_file_source.h \
    ut_network/ut_tcp_client.h \
    ut_network/ut_share_config.h \
    ut_network/ut_tcp_server.h \
    ut_score_board/ut_point.h \
    ut_score_board/ut_round.h \
    ut_score_board/ut_team.h \
    ut_timer/ut_countdowntimer.h \
    ut_timer/ut_datetimetimer.h \
    ut_timer/ut_timerformatparser.h \
    ut_timer/ut_chronodowntimer.h
