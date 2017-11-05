#-------------------------------------------------
#
# Project created by QtCreator 2017-11-03T16:47:00
#
#-------------------------------------------------

QT       -= gui

TARGET = heatercontroller
TEMPLATE = lib

DEFINES += HEATERCONTROLLER_LIBRARY

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
        heatercontroller.cpp \
    controllerplugin.cpp \
    controlleronoff.cpp

HEADERS += \
        heatercontroller.h \
        heatercontroller_global.h \ 
    controllerplugin.h \
    ../ \
    controlleronoff.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../heaterdata/release/ -lHeaterData
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../heaterdata/debug/ -lHeaterData
else:unix: LIBS += -L$$OUT_PWD/../heaterdata/ -lHeaterData

INCLUDEPATH += $$PWD/../heaterdata
DEPENDPATH += $$PWD/../heaterdata

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../heaterdata/release/libHeaterData.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../heaterdata/debug/libHeaterData.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../heaterdata/release/HeaterData.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../heaterdata/debug/HeaterData.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../heaterdata/libHeaterData.a
