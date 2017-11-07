#-------------------------------------------------
#
# Project created by QtCreator 2017-11-02T19:24:48
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_heaterdata_testtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        tst_heaterdata_testtest.cpp \

DEFINES += SRCDIR=\\\"$$PWD/\\\"


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../heaterconfig/release/ -lHeaterConfig
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../heaterconfig/debug/ -lHeaterConfig
else:unix: LIBS += -L$$OUT_PWD/../../heaterconfig/ -lHeaterConfig

INCLUDEPATH += $$PWD/../../heaterconfig
DEPENDPATH += $$PWD/../../heaterconfig

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../heaterconfig/release/libHeaterConfig.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../heaterconfig/debug/libHeaterConfig.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../heaterconfig/release/HeaterConfig.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../heaterconfig/debug/HeaterConfig.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../heaterconfig/libHeaterConfig.a