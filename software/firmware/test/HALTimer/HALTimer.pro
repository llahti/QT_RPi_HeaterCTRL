QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_start_stop_timer.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../HAL/release/ -lHAL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../HAL/debug/ -lHAL
else:unix: LIBS += -L$$OUT_PWD/../../HAL/ -lHAL

INCLUDEPATH += $$PWD/../../HAL
DEPENDPATH += $$PWD/../../HAL

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../HAL/release/libHAL.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../HAL/debug/libHAL.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../HAL/release/HAL.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../HAL/debug/HAL.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../HAL/libHAL.a
