#-------------------------------------------------
#
# Project created by QtCreator 2017-11-04T16:44:12
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_heatercontrollertest
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
    tst_heatercontrollertest.cpp \


DEFINES += SRCDIR=\\\"$$PWD/\\\"



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../heatercontroller/release/ -lheatercontroller
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../heatercontroller/debug/ -lheatercontroller
else:unix: LIBS += -L$$OUT_PWD/../../heatercontroller/ -lheatercontroller

INCLUDEPATH += $$PWD/../../heatercontroller
DEPENDPATH += $$PWD/../../heatercontroller
