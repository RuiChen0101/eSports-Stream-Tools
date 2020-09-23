QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD

SOURCES += $$files($$PWD/*.cpp, true)
SOURCES -= $$PWD/main.cpp

HEADERS += $$files($$PWD/*.h, true)

FORMS += $$files($$PWD/*.ui, true)
