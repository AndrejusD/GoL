#-------------------------------------------------
#
# Project created by QtCreator 2016-07-25T16:36:41
#
#-------------------------------------------------

QT       += testlib
QT       += widgets
QT       -= gui

TARGET = test_points
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += test_points.cpp \
    ../../points.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    test_points.h \
    ../../points.h
