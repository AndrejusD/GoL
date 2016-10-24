#-------------------------------------------------
#
# Project created by QtCreator 2016-09-26T13:05:48
#
#-------------------------------------------------

QT       += testlib
QT       += gui
QT       += widgets

TARGET = test_mainform
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += test_mainform.cpp \
    ../../mainwindow.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../mainwindow.h \
    #../../../build-GameOfLife-Desktop_Qt_5_6_1_MinGW_32bit-Debug/ui_mainwindow.h
