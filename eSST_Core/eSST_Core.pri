QT       += core network

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../eSST_Core/release/
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../eSST_Core/debug/
else:unix: LIBS += -L$$OUT_PWD/../eSST_Core/

LIBS += -leSST_Core
