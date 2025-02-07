QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = client
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
INCLUDEPATH += ../newCommon

SOURCES += \
        main.cpp \
        application.cpp \
        interface.cpp \
        ../newCommon/communicator.cpp \
    ../newCommon/common.cpp

HEADERS += \
        application.h \
        interface.h \
        ../newCommon/communicator.h \
        ../newCommon/common.h
