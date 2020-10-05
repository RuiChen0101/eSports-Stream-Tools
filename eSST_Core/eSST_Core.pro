QT -= gui
QT += network

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    file/config_file.cpp \
    file/file.cpp \
    file/file_manager.cpp \
    file/file_source.cpp \
    network/share_config.cpp \
    network/tcp_client.cpp \
    network/tcp_connection.cpp \
    network/tcp_server.cpp \
    score_board/point.cpp \
    score_board/round.cpp \
    score_board/team.cpp \
    timer/chrono_down_timer.cpp \
    timer/countdown_timer.cpp \
    timer/date_time_timer.cpp \
    timer/timer.cpp \
    timer/timer_format_parser.cpp \
    utility/signal_bus.cpp \
    utility/system_call.cpp \
    utility/timetick.cpp

HEADERS += \
    file/config_file.h \
    file/file.h \
    file/file_manager.h \
    file/file_source.h \
    network/share_config.h \
    network/tcp_client.h \
    network/tcp_connection.h \
    network/tcp_server.h \
    score_board/point.h \
    score_board/round.h \
    score_board/team.h \
    timer/chrono_down_timer.h \
    timer/countdown_timer.h \
    timer/date_time_timer.h \
    timer/timer.h \
    timer/timer_format_parser.h \
    utility/signal_bus.h \
    utility/system_call.h \
    utility/timetick.h

DISTFILES += \
    eSST_Core.pri

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
