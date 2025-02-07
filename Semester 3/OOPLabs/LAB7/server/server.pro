QT -= gui
QT += network

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ../newCommon

SOURCES += main.cpp \
    TComplex.cpp \
    application.cpp \
    ../newCommon/communicator.cpp \
    ../newCommon/common.cpp

HEADERS += \
    TComplex.h \
    TFSi.h \
    TFSin.h \
    TFunction.h \
    application.h \
    array.h \
    polynom.h \
    ../newCommon/communicator.h \
    ../newCommon/common.h
