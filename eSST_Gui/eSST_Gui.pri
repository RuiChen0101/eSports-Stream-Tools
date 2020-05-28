INCLUDEPATH += \
    $$PWD/ \

LIBS += -L$$OUT_PWD/../eSST_Gui/debug/-leSST_Gui_Lib
PRE_TARGETDEPS += $$OUT_PWD/../eSST_Gui/debug/libeSST_Gui_Lib.a
