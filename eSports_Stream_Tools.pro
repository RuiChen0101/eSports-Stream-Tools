DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = subdirs
SUBDIRS = eSST_Core \
    eSST_Controller_Gui \
    eSST_Receiver_Gui \
    eSST_Test
INCLUDEPATH += ./

CONFIG += ordered
