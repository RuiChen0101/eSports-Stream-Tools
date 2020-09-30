QT       += core network

INCLUDEPATH += $$PWD

Debug: LIBS += -L$$OUT_PWD/../eSST_Core/debug/
Release: LIBS += -L$$OUT_PWD/../eSST_Core/release/

Debug: PRE_TARGETDEPS += $$OUT_PWD/../eSST_Core/debug/libeSST_Core.a
Release: PRE_TARGETDEPS += $$OUT_PWD/../eSST_Core/release/libeSST_Core.a

LIBS += -leSST_Core
