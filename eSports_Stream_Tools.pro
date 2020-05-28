DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = subdirs
SUBDIRS = eSST_Gui

ConfigTest{
SUBDIRS += eSST_Test/gtest
SUBDIRS += eSST_Test
}

eSST_Test.depends = eSST_Gui

CONFIG += ordered
