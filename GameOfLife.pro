#-------------------------------------------------
#
# Project created by QtCreator 2016-04-24T11:15:48
#
#-------------------------------------------------

QT       += core gui #opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameOfLife
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customscene.cpp \
    points.cpp

HEADERS  += mainwindow.h \
    customscene.h \
    points.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES +=
