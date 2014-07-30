#-------------------------------------------------
#
# Project created by QtCreator 2014-07-29T20:45:40
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lamp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    authwin.cpp

HEADERS  += mainwindow.h \
    authwin.h \
    structs.h

FORMS    += mainwindow.ui \
    authwin.ui
